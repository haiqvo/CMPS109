GCC       = g++ -std=c++11

MKFILE    = Makefile
SOURCES   = hexboard.cc
EXECBIN   = hexboard
OBJECTS   = $(SOURCES:.cc=.o)

all:
		$(GCC) -o $(EXECBIN) $(SOURCES)

clean:
		- rm $(EXECBIN)
