GCC       = g++ -std=c++11

MKFILE    = Makefile
SOURCES   = test.cc
EXECBIN   = test
OBJECTS   = $(SOURCES:.cc=.o)

all:
		$(GCC) -o $(EXECBIN) $(SOURCES)

clean:
		- rm $(EXECBIN)
