CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lcurl
SOURCES=main.cpp console/ansi.cpp security.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin/fas
INSTALL_DIR=/usr/local

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

install:
	install -m 0755 $(EXECUTABLE) $(INSTALL_DIR)/bin

.PHONY: install
