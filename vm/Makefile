OS_TYPE := $(shell sh -c 'uname -s')
COMO_OBJECT_LIB=-lcomoobject
COMO_OBJECT_LIB_LD_FLAGS= -shared
BINDIR = $(HOME)/objlib/bin
CFLAGS = -rdynamic -O0 -Wall -Wextra -g -ggdb -std=c99 -I$(HOME)/objlib/src -L$(BINDIR) -Wl,-rpath=$(BINDIR)
LIBS := $(COMO_OBJECT_LIB)
SOURCES = $(shell echo *.c)
COMO_OBJECT_LIB_OBJECTS =vm3

all: $(COMO_OBJECT_LIB_OBJECTS)

.c:
	$(CC) como_debug.c $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf vm3
