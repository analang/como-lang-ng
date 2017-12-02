#include <assert.h>
#include <limits.h>
#include <como.h>
#include <stdarg.h> 

#define COMO_WARNING 1
#include "como_debug.h"

#include "../como_opcode.h"

static int gc_on = 0;

static void do_gc(como_frame *frame);
static void dump_locals(como_frame *frame);

#define should_grow(f) como_frame_growstack((como_object *)f)

#define gc_new(frame, obj) \
  gc_new_ex(frame, obj, 1, __FUNCTION__, __FILE__, __LINE__)

#define gc_new_noref(frame, obj) \
  gc_new_ex(frame, obj, 0, __FUNCTION__, __FILE__, __LINE__)

static como_object *gc_new_ex(
  como_frame *frame, como_object *obj, int initrefcount, const char *fn, 
  const char *file, int lineno)
{  
  frame->nobjslt++;

#if COMO_WARNING
  como_object *str = obj->type->obj_str(obj);
  como_warning("\t%p is of type %s with value `%s`",
    (void *)obj, como_type_name(obj), ((como_string *)str)->value);
  como_warning("\t\tallocated on line %d", lineno);
  como_object_dtor(str);
#endif

  if(frame->nobjs >= frame->mxobjs)
    if(gc_on)
      do_gc(frame);

  obj->next = frame->root;
  obj->flags = initrefcount;

  frame->root = obj;

  frame->nobjs++;

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

static char *make_except(const char *fmt, ...)
{
  char *buffer = NULL;
  int size = 1024;
  va_list args;
  va_start (args, fmt);
  buffer = malloc(size + 1);
  vsnprintf(buffer, size, fmt, args);
  va_end (args);
  return buffer;
}

#define int_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_longfromlong(value))), \
  (como_container_size(frame->constants) - 1))

#define str_const(frame, value) \
  (como_array_push(frame->constants, gc_new(frame, como_stringfromstring(value))), \
  (como_container_size(frame->constants) - 1))

#define str_const_posunrc(frame, value) \
  (como_array_push(frame->constants, gc_new_noref(frame, como_stringfromstring(value))), \
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

#ifdef COMO_WARNING
#define decref(o) do { \
    como_size_t prev = o->flags; \
    --o->flags; \
    como_warning("decref for %p, old is %ld, new is %ld", (void *)o, prev, \
      o->flags); \
    como_warning("\tat %s %d", __FUNCTION__, __LINE__); \
} while(0)
#else
#define decref(o) --o->flags
#endif

#define incref(o) o->flags++

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
char *ex = NULL;

((como_object *)frame)->type->obj_init((como_object *)frame);

#define set_except(fmt, ...) \
  ex = make_except(fmt, ##__VA_ARGS__)

  for(;;) {
    top:
    /* Reset result */
    result = NULL;
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
        push(result);
        vm_continue();
      }
      vm_target(LOAD_NAME) {
        arg = get_const(get_arg());
        result = como_map_get(frame->locals, arg);
        if(result) {
          push(result);
          incref(result);
        }
        else {
          set_except("NameError, undefined variable `%s`", ((como_string *)arg)->value);
        }
        vm_continue();
      }
      vm_target(IADD) {
        right = pop();
        left  = pop();
        result = add(frame, left, right);
        
        decref(right);
        decref(left);

        if(result) {
          push(result);
        }
        else
          set_except("unsupported operands for + operator");
        vm_continue();
      }
      vm_target(IMINUS) {
        right = pop();
        left  = pop();
        result = sub(frame, left, right);

        decref(right);
        decref(left);

        if(result) {
          push(result);
        }
        else
          set_except("unsupported operands for - operator");
        vm_continue();
      }
      vm_target(ITIMES) {
        right = pop();
        left  = pop();
        result = mul(frame, left, right);
        
        decref(right);
        decref(left);

        if(result) {
          push(result);
        }
        else
          set_except("unsupported operands for * operator");
        vm_continue();      
      }
      vm_target(IDIV) {
        right = pop();
        left  = pop();
        result = do_div(frame, left, right);

        decref(right);
        decref(left);

        if(result) {
          push(result);
        }
        else
          set_except("unsupported operands for / operator");
        vm_continue();
      }
      vm_target(IREM) {
        right = pop();
        left  = pop();
        result = rem(frame, left, right);

        decref(right);
        decref(left);

        if(result) {
          push(result);
        }
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

        decref(right);
        decref(left);

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

        if(result)
          push(result);
        else 
          set_except("unsupported operand types for <= operator");

        decref(right);
        decref(left);
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
          free(ex);
          ex = NULL;
          goto top;
        }
      }
      fprintf(stdout, "como: fatal, unhandled exception: %s\n", ex);
      free(ex);
      ex = NULL;
      goto exit;
    }
  }

exit:

 // while(!empty())
//  {
    //como_object *obj = pop();
    //decref(obj);
 // }

  dump_locals(frame);

  ((como_object *)frame)->type->obj_deinit((como_object *)frame);

  do_gc(frame);

  como_object_dtor((como_object *)frame);

  return retval; 
}

static void dump_locals(como_frame *frame)
{
  como_warning("symbol table for frame %s", ((como_string *)frame->name)->value);
  como_map *map = (como_map *)frame->locals;
  como_size_t i;
  como_warning("%s: total %ld", ((como_string *)frame->name)->value, map->size);

  for(i = 0; i < map->capacity; i++)
  {
    como_map_bucket *bucket = map->buckets[i];

    while(bucket) 
    {
      como_object *key = bucket->key->type->obj_str(bucket->key);
      como_object *value = bucket->value->type->obj_str(bucket->value);

      como_warning("\t%s: %s", ((como_string *)key)->value, 
        ((como_string *)value)->value);

      bucket = bucket->next;

      como_object_dtor(key);
      como_object_dtor(value);
    }
  }
}

static void do_gc(como_frame *frame)
{
#ifdef COMO_WARNING
  #define COUNT_EX(v) do { \
    int ncount = 0; \
    como_object *n = frame->root; \
    while(n) \
    { \
      ncount++; \
      n = n->next; \
    } \
    como_warning("%d objects in root", ncount); \
    if(v) { \
      n = frame->root; \
      while(n) \
      { \
        como_warning("\t%p, refcount %ld", (void *)n, n->flags); \
        n = n->next; \
      } \
    } \
  } while(0)

  #define SHOW_OBJS_LEFT() COUNT_EX(1)
  #define COUNT() COUNT_EX(0)
#else
  #define COUNT()
  #define SHOW_OBJS_LEFT()
#endif

  como_warning("/// begin gc cycle");
  COUNT();

  como_object **root = &frame->root;

  while(*root)
  {
    if((*root)->flags <= 0 ) 
    {
      como_object *unreached = *root;
      como_warning("como_object_dtor(%p), refcount=%ld", 
        (void *)unreached, unreached->flags);
      como_object *next = unreached->next;
      como_object_dtor(unreached);
      *root = next;
      frame->nobjs--;
    }
    else {
      como_warning("refcount for %p is at %ld, not releasing",
        (void *)(*root), (*root)->flags);
      root = &(*root)->next;
    }
  }

  SHOW_OBJS_LEFT();
  como_warning("\\\\\\ end gc cycle");
}

int main(void)
{
  como_frame *frame = (como_frame *)como_frame_new("__como_start", NULL);
  
  #include "program.c"

  gc_on = 1;
  como_object *retval = como_frame_eval(frame);

  if(retval)
  {
    como_object *strval = retval->type->obj_str(retval);
    fprintf(stdout, "%p $returnValue=%s\n", 
      (void *)retval, ((como_string *)strval)->value);
    como_object_dtor(strval);
    decref(retval);
    como_object_dtor(retval);
  }

  return 0;
}
