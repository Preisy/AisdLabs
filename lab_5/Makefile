CC=g++ -std=c++14
CFLAGS=-c -Wall -Isrc -Ilib -Idigraph -w
LDFLAGS=
SOURCES=startup.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	find -not \( -wholename '*/cmake-build-debug/*' \) -name '*.o' -delete
