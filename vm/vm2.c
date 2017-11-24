#include <assert.h>
#include <como.h>

#include "../como_opcode.h"

typedef struct _como_frame {
  como_object *name; 
  como_object *code;
  como_object *constants;
  como_object *locals;
  como_object **stack;
  como_object *root;
  como_size_t pc;
  como_size_t sz;
  como_size_t sp;
} como_frame;

static void como_frame_dtor(como_frame *f)
{
  como_object_dtor(f->name);
  como_object_dtor(f->code);
  como_object_dtor(f->constants);
  como_object_dtor(f->locals);
  free(f->stack);
  free(f);
}

static como_frame *como_frame_new(char *name)
{
  como_frame *f = malloc(sizeof(*f));

  f->name      = como_stringfromstring(name);
  f->code      = como_array_new(8);
  f->constants = como_array_new(8);
  f->locals    = como_map_new(8);
  f->stack     = malloc(sizeof(como_object *) * 255);
  
  f->pc        = 0;
  f->sp        = 0; 
  f->sz        = 255;
  f->root      = NULL;

  int i;
  for(i = 0; i < 255; i++)
    f->stack[i] = NULL;

  return f;
}

static void should_grow(como_frame *frame)
{
  if(frame->sp >= frame->sz)
  {
    frame->sz = frame->sz * 2;
    frame->stack = realloc(frame->stack, sizeof(como_object *) * frame->sz);
  }
}

static como_object *gc_new(como_frame *frame, como_object *obj)
{
  obj->next = frame->root;
  obj->flags = 0;

  frame->root = obj;

  return obj;
}

static como_object *add(como_frame *f, como_object *a, como_object *b)
{
  if(a->type->obj_binops != NULL && a->type->obj_binops->obj_add != NULL)
    return gc_new(f, a->type->obj_binops->obj_add(a, b));
  return NULL;
}

#define int_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_longfromlong(value))), \
  (como_container_size(frame->constants) - 1))

#define str_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_stringfromstring(value))), \
  (como_container_size(frame->constants) - 1))

#define PACK_INSTRUCTION(opcode, argument, flag) \
    (como_uint32_t)((((uint8_t)(opcode)) << 24) | \
    (((uint16_t)(argument)) << 8) | \
    ((uint8_t)(flag)))

#define emit(frame, opcode, arg, flag) \
    como_code_push(frame->code, PACK_INSTRUCTION(opcode, arg, flag))

static como_object *como_frame_eval(como_frame *frame)
{
#define vm_case(o) switch(o)

#define vm_target(x) case x:

#define vm_continue() break

#define fetch() (frame->pc++, (((como_code_get(frame->code, frame->pc -1) >> 24) & 0xff)))

#define get_const(x) \
  como_array_get(frame->constants, x)

#define get_arg() \
  ((como_code_get(frame->code, frame->pc -1) >> 8) & 0xffff)

#define push(arg) \
  (should_grow(frame), (frame->stack[frame->sp++] = arg))

#define pop() \
  (frame->stack[--frame->sp])

#define empty() \
  (frame->sp == 0)

como_object *arg;
como_object *retval = NULL;
como_object *left, *right, *result;
const char *ex = NULL;

#define set_except(x) \
  ex = x;

  for(;;) {
    vm_case(fetch()) {
      vm_target(LOAD_CONST) {
        arg = get_const(get_arg());
        push(arg);
        vm_continue();
      }
      vm_target(STORE_NAME) {
        arg = get_const(get_arg());
        result = pop();
        como_map_put(frame->locals, arg, result);
        vm_continue();
      }
      vm_target(LOAD_NAME)
      {
        arg = get_const(get_arg());
        result = como_map_get(frame->locals, arg);
        if(result)
          push(result);
        else
          set_except("undefined variable");
        vm_continue();
      }
      vm_target(IADD) {
        right = pop();
        left  = pop();
        result = add(frame, left, right);
        if(result)
          push(result);
        else
          set_except("unsupported operands for + operator");
        vm_continue();
      }
      vm_target(IRETURN) {
        if(!empty()) 
          retval = pop();
        goto exit;
      }
      vm_target(IPRINT) {
        result = pop();
        como_object_print(result);
        vm_continue();
      }
    }

    if(ex) {
      fprintf(stdout, "Exception: %s\n", ex);
      goto exit;
    }
  }

exit:
  fprintf(stderr, "returning from eval loop:\n");
  fprintf(stderr, "sp=%ld\n", frame->sp);
  return retval;  
}


static void do_gc(como_frame *frame)
{
  /* Mark */
  int i;
  for(i = 0; i < frame->sz; i++)
  {
    como_object *obj = frame->stack[i];

    if(obj)
      obj->flags = 1;
  }
  /* Sweep */
  como_object *root = frame->root;

  while(root != NULL)
  {
    como_object *next = root->next;
    /* if this object is marked, free it and set root to next */
    if(root->flags) {
      como_object_dtor(root); 
      root = next;
    }
    else {
      root->flags = 1;
      /* else set this object to marked, 
         and go backt to top to hit top branch 
         */
    }
  }
}


int main(void)
{

  como_frame *mainframe = como_frame_new("main");

  emit(mainframe, LOAD_CONST, int_const(mainframe, 15), 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 5),  0);
  emit(mainframe, IADD,       0, 0);
  emit(mainframe, STORE_NAME, str_const(mainframe, "sum"), 0);
  emit(mainframe, LOAD_NAME,  str_const(mainframe, "sum"), 0);
  emit(mainframe, IPRINT,     0, 0);
  emit(mainframe, IRETURN,    0, 0);

  como_object *result = como_frame_eval(mainframe);

  if(result)
    como_object_print(result);

  do_gc(mainframe);
  como_frame_dtor(mainframe);

  return 0;
}