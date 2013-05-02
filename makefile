CC=g++
CFLAGS=-std=c++0x -c -Wall -ggdb
LDFLAGS=
SOURCES=$(wildcard src/*.cc)
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cc=.o)))
EXECUTABLE=bin/cmdline_gen

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
		
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.cc
	$(CC) $(CFLAGS) $< -o $@
