CFLAGS = -g -Wall -Wextra -Wunused-parameter
LIBS = -lobject
YACC = bison
YFLAGS = -y --warnings=all
LEX = flex

como: como_object.o como_ast_free.o como_io.o como_executor.o como_ast.o como_debug.o como_stack.o como_lexer.o como_parser.o como_compiler.o como.o
	$(CC) como_io.o como_object.o como_executor.o como_debug.o como_ast.o como_stack.o como_parser.o como_lexer.o como_compiler.o como_ast_free.o como.o -o como $(CFLAGS) $(LIBS)

como_lexer.o: como_parser.c como_lexer.l

clean:
	rm -f *.o como_lexer.c como_lexer.h como_parser.c como_parser.h como

