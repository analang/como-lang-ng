#include <assert.h>
#include <limits.h>
#include <como.h>

#include "../como_opcode.h"

typedef struct _como_frame {
  como_object *name; 
  como_object *code;
  como_object *constants;
  como_object *locals;
  como_object **stack;
  /* TODO, more roots, one per each frame */
  como_object *root;
  como_size_t pc;
  como_size_t sz;
  como_size_t sp;
} como_frame;

/* TODO, since functions can be stored as names,
  I should create a function_object, (a subclass of como_object
  which is basically just a frame object */
/* I can perhaps create a frame object with a code object as argument */
/* Then I can implement a constructor, destructor for the function object 
   to be called when it is called, and finished from calling */
static void como_frame_dtor(como_frame *f)
{
  como_object_dtor(f->name);
  como_object_dtor(f->code);
  /* Each time a function is called, these need to be cleared */
  como_object_dtor(f->constants);
  como_object_dtor(f->locals);

  free(f->stack);
  free(f);
}

static como_frame *como_frame_new(char *name)
{
  como_frame *f = malloc(sizeof(*f));

  f->name      = como_stringfromstring(name);
  f->code      = como_code_new(8);
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

static como_object *sub(como_frame *f, como_object *a, como_object *b)
{
  if(a->type->obj_binops != NULL && a->type->obj_binops->obj_sub != NULL)
    return gc_new(f, a->type->obj_binops->obj_sub(a, b));
  return NULL;
}

static como_object *mul(como_frame *f, como_object *a, como_object *b)
{
  if(a->type->obj_binops != NULL && a->type->obj_binops->obj_mul != NULL)
    return gc_new(f, a->type->obj_binops->obj_mul(a, b));
  return NULL;
}

static como_object *rem(como_frame *f, como_object *a, como_object *b)
{
  if(a->type->obj_binops != NULL && a->type->obj_binops->obj_rem != NULL)
    return gc_new(f, a->type->obj_binops->obj_rem(a, b));
  return NULL;
}

static como_object *do_div(como_frame *f, como_object *a, como_object *b)
{
  if(a->type->obj_binops != NULL && a->type->obj_binops->obj_div != NULL)
    return gc_new(f, a->type->obj_binops->obj_div(a, b));
  return NULL;
}

static como_object *unaryminus(como_frame *f, como_object *a)
{ 
  if(a->type->obj_binops != NULL && a->type->obj_unops->obj_minus != NULL)
    return gc_new(f, a->type->obj_unops->obj_minus(a));
  return NULL;
}

static como_object *unaryplus(como_frame *f, como_object *a)
{ 
  if(a->type->obj_binops != NULL && a->type->obj_unops->obj_plus != NULL)
    return gc_new(f, a->type->obj_unops->obj_plus(a));
  return NULL;
}

static como_object *isequal(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_eq(a, b));
}

static como_object *nequal(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_neq(a, b));
}

static como_object *isgt(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_gt(a, b)); 
}

static como_object *islt(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_lt(a, b)); 
}

static como_object *islte(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_lte(a, b)); 
}

static como_object *isgte(como_frame *f, como_object *a, como_object *b)
{
  return gc_new(f, a->type->obj_compops->obj_gte(a, b)); 
}

/* C truthness */
static int truthy(como_object *a) 
{
  return a->type->obj_bool(a) != 0;
}

static void do_gc(como_frame *frame);

/*
 * TODO, currently max index is USHRT_MAX, but there are no checks for that
 * limit...
 */
#define int_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_longfromlong(value))), \
  (como_container_size(frame->constants) - 1))

#define str_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_stringfromstring(value))), \
  (como_container_size(frame->constants) - 1))

#define dbl_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_doublefromdouble(value))), \
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

#define getflag() (((como_code_get(frame->code, frame->pc -1)) & 0xff))

como_object *arg;
como_object *retval = NULL;
como_object *left, *right, *result;
const char *ex = NULL;

#define set_except(x) \
  ex = x;

  for(;;) {
    top:
    vm_case(fetch()) {
      vm_target(JMP) {
        frame->pc = get_arg();
        goto top;
      }
      vm_target(JZ) {
        result = pop();
        if(!truthy(result)) {
          frame->pc = (como_size_t)get_arg();
          goto top;
        }
        vm_continue();
      }
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
      vm_target(LOAD_NAME){
        arg = get_const(get_arg());
        result = como_map_get(frame->locals, arg);
        if(result)
          push(result);
        else
          set_except("NameError, undefined variable");
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
      vm_target(IMINUS) {
        right = pop();
        left  = pop();
        result = sub(frame, left, right);
        if(result)
          push(result);
        else
          set_except("unsupported operands for - operator");
        vm_continue();
      }
      vm_target(ITIMES) {
        right = pop();
        left  = pop();
        result = mul(frame, left, right);
        if(result)
          push(result);
        else
          set_except("unsupported operands for * operator");
        vm_continue();      
      }
      vm_target(IDIV) {
        right = pop();
        left  = pop();
        result = do_div(frame, left, right);
        if(result)
          push(result);
        else
          set_except("unsupported operands for / operator");
        vm_continue();
      }
      vm_target(IREM) {
        right = pop();
        left  = pop();
        result = rem(frame, left, right);
        if(result)
          push(result);
        else
          set_except("unsupported operands for % operator");
        vm_continue();         
      }
      vm_target(UNARY_MINUS) {
        left = pop();
        result = unaryminus(frame, left);
        if(result)
          push(result);
        else
          set_except("unsupported operand for unary -");
        vm_continue();
      }
      vm_target(UNARY_PLUS) {
        left = pop();
        result = unaryplus(frame, left);
        if(result)
          push(result);
        else
          set_except("unsupported operand for unary +");
        vm_continue();
      }
      vm_target(IRETURN) {
        /* getflag() determine if the frame is returning a value */
        if(getflag() && !empty())
          retval = pop();
        goto exit;
      }
      vm_target(IPRINT) {
        result = pop();
        como_object_print(result);
        fputc('\n', stdout);
        vm_continue();
      }
      vm_target(EQUAL) {
        right = pop();
        left  = pop();
        result = isequal(frame, left, right);
        push(result);
        vm_continue();
      }
      vm_target(NEQUAL) {
        right = pop();
        left  = pop();
        result = nequal(frame, left, right);
        push(result);
        vm_continue();
      }
      vm_target(GT) {
        right = pop();
        left  = pop();
        result = isgt(frame, left, right);
        push(result);
        vm_continue();
      }
      vm_target(LT) {
        right = pop();
        left  = pop();
        result = islt(frame, left, right);
        push(result);
        vm_continue();
      }
      vm_target(GTE) {
        right = pop();
        left  = pop();
        result = isgte(frame, left, right);
        push(result);
        vm_continue();
      }
      vm_target(LTE) {
        right = pop();
        left  = pop();
        result = islte(frame, left, right);
        push(result);
        vm_continue();
      }
    }

    if(ex) {
      /* Find the exception handler */
      como_size_t cpc = frame->pc;
      while(--cpc)
      {
        como_uint32_t opline;
        opline = como_code_get(frame->code, cpc);
        if(((opline >> 24) & 0xff) == TRY)
        {
          frame->pc = (opline >> 8) & 0xffff;
          
          /* Now, determine what the variable name is for the catch statement */
          como_uint32_t nextop = como_code_get(frame->code, frame->pc + 1);
          if(((nextop >> 24) & 0xff) == LOAD_NAME)
          {
            como_size_t constindex = (nextop >> 8) & 0xffff;
            como_object *name = get_const(constindex);
            como_map_put(frame->locals, name, gc_new(frame, como_stringfromstring(
              (char *)ex)));
          }
          ex = NULL;
          goto top;
        }
      }
      fprintf(stdout, "como: fatal, unhandled exception: %s\n", ex);
      goto exit;
    }
  }

exit:
  while(!empty())
    (void)pop();

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
      /* This object is unreachable */
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
  
  /*
   * sum = 15 + 15;
   * print(sum * 5 == 100);
   * print(2.455 % 2);
   * if(sum == 30)
   * {
   *    print("sum is 30");
   * }
   * print("returning from main");
   * 
   * try 
   * {
   *    name = "This" - "This";
   *    print("not reached...");
   * }
   * catch(e)
   * {
   *    print(e);
   * }
   *
   *
   *
   */
  /*
   * BEGIN_TRY <CATCH_TARGET>
   *
   *
   *
   * CATCH
   *
   *
   * END_TRY
   */
  emit(mainframe, LOAD_CONST, int_const(mainframe, 15), 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 5),  0);
  emit(mainframe, IADD,       0, 0);
  emit(mainframe, STORE_NAME, str_const(mainframe, "sum"), 0);
  emit(mainframe, LOAD_NAME,  str_const(mainframe, "sum"), 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 5),     0);
  emit(mainframe, ITIMES,     0, 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 100),   0);
  emit(mainframe, EQUAL,      0, 0);
  emit(mainframe, IPRINT,     0, 0);
  emit(mainframe, LOAD_CONST, dbl_const(mainframe, 2.455), 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 2),     0);
  emit(mainframe, IREM,       0, 0);
  emit(mainframe, IPRINT,     0, 0);
  emit(mainframe, LOAD_CONST, int_const(mainframe, 30),    0);
  emit(mainframe, LOAD_NAME,  str_const(mainframe, "sum"), 0);
  emit(mainframe, EQUAL,      0, 0);
  /* Jump target is always X many instructions forward to the target 
     instruction 
  */

  if((como_container_size(mainframe->code) + 6) > USHRT_MAX)
  {
    fprintf(stderr, "como: fatal error, jump target is too big, requested: "
      "%ld, max: %hu", como_container_size(mainframe->code) + 6, USHRT_MAX);

    exit(1);
  }

  emit(mainframe, JZ,         como_container_size(mainframe->code) + 3, 0);
  emit(mainframe, LOAD_CONST, str_const(mainframe, "sum is 30"),      0);
  emit(mainframe, IPRINT,     0, 0);



  if((como_container_size(mainframe->code) + 6) > USHRT_MAX)
  {
    fprintf(stderr, "como: fatal error, jump target is too big, requested: "
      "%ld, max: %hu", como_container_size(mainframe->code) + 6, USHRT_MAX);

    exit(1);
  }

  emit(mainframe, TRY,        como_container_size(mainframe->code) + 6, 0);
  emit(mainframe, LOAD_CONST, str_const(mainframe, "This"),             0);
  emit(mainframe, LOAD_CONST, str_const(mainframe, "This"),             0);
  emit(mainframe, ITIMES,    0, 0);
  emit(mainframe, LOAD_CONST, str_const(mainframe, "not reached..."), 0);
  emit(mainframe, IPRINT,    0, 0);
  emit(mainframe, CATCH,     0, 0);
  emit(mainframe, LOAD_NAME, str_const(mainframe, "e"), 0);
  emit(mainframe, IPRINT,    0, 0);
  emit(mainframe, LOAD_CONST, str_const(mainframe, "returning from main"), 0);
  emit(mainframe, IPRINT,     0, 0);
  emit(mainframe, IRETURN,   0, 0);

  como_object *result = como_frame_eval(mainframe);

  if(result) {
    printf("return val: ");
    como_object_print(result);
  }

  do_gc(mainframe);
  como_frame_dtor(mainframe);

  return 0;
}
