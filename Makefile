CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lcurl
SOURCES=main.cpp ansi.cpp security.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fas

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
