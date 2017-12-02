emit(frame, LOAD_CONST, int_const(frame, 15), 0);
emit(frame, LOAD_CONST, int_const(frame, 5),  0);
emit(frame, IADD,       0, 0);
emit(frame, STORE_NAME, str_const(frame, "sum"), 0);
emit(frame, IPRINT,     0, 0);
emit(frame, IRETURN,    0, 0);