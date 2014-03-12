GCC       = g++ -std=c++11
ARGS	  = -Wall -Wextra -lglut -lGL
#g++ -std=c++11 -Wall -Wextra -lglut -lGL -c glut_test.cpp
#g++ -std=c++11 -Wall -Wextra -lglut -lGL -o test glut_test.o

MKFILE    = Makefile
SOURCES   = glut_test.cpp
EXECBIN   = test
OBJECTS   = $(SOURCES:.cpp=.o)

all:
		$(GCC) $(ARGS) -c  $(SOURCES)
		$(GCC) $(ARGS) -o $(EXECBIN)  $(OBJECTS)

clean:
		- rm $(EXECBIN) $(OBJECTS)
