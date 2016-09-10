CFLAGS = -g -Wall -Wextra
LIBS = -lobject -leasyio

como: como_ast.o como_debug.o como_stack.o como_lexer.o como_parser.o como_compiler.o como.o
	$(CC) como_debug.o como_ast.o como_stack.o como_parser.o como_lexer.o como_compiler.o como.o -o como $(CFLAGS) $(LIBS)

como_ast.o: como_ast.c
	$(CC) $(CFLAGS) -c como_ast.c

como_compiler.o: como_compiler.c
	$(CC) $(CFLAGS) -c como_compiler.c

como_stack.o: como_stack.c
	$(CC) $(CFLAGS) -c como_stack.c

como_lexer.o: como_lexer.c
	$(CC) $(CFLAGS) -c como_lexer.c

como_debug.o: como_debug.c
	$(CC) $(CFLAGS) -c como_debug.c

como_lexer.c: como_parser.c como_lexer.l
	flex como_lexer.l

como_parser.o: como_parser.c
	$(CC) $(CFLAGS) -c como_parser.c

como_parser.c: como_parser.y
	bison --warnings=all como_parser.y

como.o: como.c
	$(CC) $(CFLAGS) $(LIBS) -c como.c
clean:
	rm -f *.o como_lexer.c como_lexer.h como_parser.c como_parser.h como

