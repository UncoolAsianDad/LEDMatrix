
CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lwiringPi
SOURCES=src/LEDMatrix.cpp src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=led_matrix

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o build/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f src/*.o
	rm -f build/$(EXECUTABLE)
