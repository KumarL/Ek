CC=g++
CFLAGS=-std=c++0x -c -Wall -ggdb
LDFLAGS=
SOURCES=$(wildcard *.cc)
OBJECTS=$(patsubst %.cc, %.o, $(SOURCES))
EXECUTABLE=../bin/cmdline_gen

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
