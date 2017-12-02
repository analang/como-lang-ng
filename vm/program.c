/* sum = 15 + 5 */
emit(frame, LOAD_CONST, int_const(frame, 15), 0);
emit(frame, LOAD_CONST, int_const(frame, 5),  0);
emit(frame, IADD,       0, 0);
emit(frame, STORE_NAME, str_const(frame, "sum"), 0);

/* print sumcopy = sum */
emit(frame, LOAD_NAME,  str_const(frame, "sum"), 0); 
emit(frame, STORE_NAME, str_const(frame, "sumcopy"), 0);
emit(frame, IPRINT,     0, 0);


/* result = 5 * 5; */
emit(frame, LOAD_CONST, int_const(frame, 5), 0);
emit(frame, LOAD_CONST, int_const(frame, 5), 0);
emit(frame, ITIMES,     0, 0);
emit(frame, STORE_NAME, str_const(frame, "result"), 0);

/* print sum == result */
emit(frame, LOAD_NAME, str_const(frame, "sum"), 0);
emit(frame, LOAD_NAME, str_const(frame, "result"), 0);
emit(frame, EQUAL,      0, 0);
emit(frame, IPRINT,     0, 0);


/* add(26, 1); */
emit(frame, LOAD_CONST, int_const(frame, 26), 0);
emit(frame, LOAD_CONST, int_const(frame, 1),  0);
emit(frame, LOAD_NAME,  str_const(frame, "add"), 0);
emit(frame, CALL,       2, 0);


/* print "returning " + "from main"; */
emit(frame, LOAD_CONST, str_const(frame, "returning "), 0);
emit(frame, LOAD_CONST, str_const(frame, "from main"),  0);
emit(frame, IADD,       0, 0);
emit(frame, IPRINT,     0, 0);




/* return 1; */
emit(frame, LOAD_CONST, int_const(frame, 0), 0);
emit(frame, IRETURN,    0, 1);