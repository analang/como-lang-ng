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
        decref(arg);
        //incref(result);
        push(result);
        vm_continue();
      }
      vm_target(LOAD_NAME){
        arg = get_const(get_arg());
        result = como_map_get(frame->locals, arg);
        if(result) {
          push(result);
        }
        else {
          set_except("NameError, undefined variable `%s`", ((como_string *)arg)->value);
        }
        decref(arg);
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
        decref(result);
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
  while(!empty()) {
    como_object *obj = pop();
    como_warning("%p was on stack at end of frame eval, refcount at %ld",
      (void *)obj, obj->flags);
    decref(obj);
  }

  do_gc(frame);

  ((como_object *)frame)->type->obj_deinit((como_object *)frame);

  como_object_dtor((como_object *)frame);

  return retval;