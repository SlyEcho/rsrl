
CC = g++

FLAGS = -std=gnu++0x 
CFLAGS = -pedantic -Wall -ggdb3
LDFLAGS = -lncurses
DEBUGFLAGS = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

TARGET = rsrl
SOURCES := $(wildcard *.cc)
HEADERS := $(wildcard *.h)
OBJECTS := $(SOURCES:.cc=.o)

all:	$(TARGET)

$(TARGET):	$(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS)  $(OBJECTS) -o $(TARGET)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)

.SECONDEXPANSION:

$(foreach OBJ,$(OBJECTS),$(eval $(OBJ)_DEPS = $(shell g++ -std=gnu++0x -MM $(OBJ:.o=.cc) | sed s/.*://)))
%.o: %.cc $$($$@_DEPS)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<
  
.PHONY:	all clean

