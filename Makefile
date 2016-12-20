.PHONY: all clean

CFLAGS=-O2 -Wall -I. -std=c99
CXXFLAGS=-O2 -Wall -I. -std=c99
AR=ar
CC=gcc
CXX=g++

ifeq ($(OS),Windows_NT)
  RM=del
  CFLAGS += -D__USE_MINGW_ANSI_STDIO=1
else
  RM=rm
  UNAME := $(shell uname)
  ifeq ($(UNAME), Darwin)
    CFLAGS += $(CFLAGS) -arch x86_64
    CXXFLAGS += -arch x86_64
  endif
endif

all: librope.a

clean:
	$(RM) -f librope.a *.bc *.o tests

# You can add -emit-llvm here if you're using clang.
rope.o: rope.c rope.h
	$(CC) $(CFLAGS) $< -c -o $@

librope.a: rope.o
	$(AR) -rcs $@ $^

# Only need corefoundation to run the tests on mac
tests: test/tests.c test/benchmark.c test/slowstring.c librope.a
	$(CC) $(CFLAGS) -o $@ $^

