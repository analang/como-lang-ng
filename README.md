# COMO: como object meta oriented

# even.como
```
func isodd(num) {
	i = 0;
	odd = 0;
	while((i == num) == 0) {
		if(odd == 0) {
			odd = 1;
		} else {
			odd = 0;
		}
		i = i + 1;
	}
	return odd;
}

func print_even(num)
{
	while(num) {
		if(isodd(num)) {
			print(num + " is odd");
		} else {
			print(num + " is even");
		}
		num = num - 1;
	}
}

print_even(4);
```

# range
```
func print_range(a, b) {
	while(a <= b) {
		print(a);
		a = a + 1;
	}
}
```

# Build Requirements
I only compile this on UNIX like systems. You need the standard build tools
such as `autoconf`, `libtool`, and `flex` and `bison`. Also there is a runtime
requirement : `libobject` which you can get at https://github.com/libobject/libobject

# License
Please see the file LICENSE located in the root directory of the project.


# Virtual Machine
The compiler generates instructions of the custom instruction set (como_opcode.h) The virtual machine is stack based and only a few instructions take operands. Most instructions pop there arguments from the stack. Here is the relevant source code and instruction output generated from the compiler. This was run with the following command: `./como --print-asm test/for_loop`

```
for(i = 5; i >= 0; i--)
{
  if(i % 2 == 0) {
    print(i);
  }
}
```

```
0       LABEL
1       LOAD_CONST 5
2       STORE_NAME i
3       LOAD_NAME i
4       LOAD_CONST 0
5       IS_GREATER_THAN_OR_EQUAL
6       JZ 25
7       LABEL
8       LOAD_NAME i
9       LOAD_CONST 2
10      IREM
11      LOAD_CONST 0
12      IS_EQUAL
13      JZ 17
14      LOAD_NAME i
15      IPRINT
16      JMP 18
17      LABEL
18      LABEL
19      POSTFIX_DEC
20      LOAD_NAME i
21      LOAD_CONST 0
22      IS_GREATER_THAN_OR_EQUAL
23      JZ 25
24      JMP 7
25      LABEL
26      HALT
```
