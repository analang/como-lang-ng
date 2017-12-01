OS_TYPE := $(shell sh -c 'uname -s')
COMO_OBJECT_LIB=-lcomoobject
COMO_OBJECT_LIB_LD_FLAGS= -shared
BINDIR = $(HOME)/objlib/bin
CFLAGS = -Wall -Wextra -g -ggdb -std=c99 -I$(HOME)/objlib/src -L$(BINDIR) -Wl,-rpath=$(BINDIR)
LIBS := $(COMO_OBJECT_LIB)
SOURCES = $(shell echo *.c)
COMO_OBJECT_LIB_OBJECTS =vm2

all: $(COMO_OBJECT_LIB_OBJECTS)

.c:
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf bin/*
