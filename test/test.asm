;
; print(typeof 1);
;

1  PUSH 1    ; push 1 onto the stack 
2  TYPEOF    ; pop the stack, determine the object type, and push result
3  PRINT     ; pop the stack, and print the object
4  IRETURN 0 ; return with no value, 0 indiciates there is no return value to be popped from the stack
5  HALT      ; end execution\


0 newObject(1)
pop, got object 0
push newString (1)
POP, got object 1
