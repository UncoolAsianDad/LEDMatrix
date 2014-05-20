
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lwiringPi
SOURCES=src/LEDMatrix.cpp src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=led_matrix

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	mkdir -p build
	$(CC) $(LDFLAGS) $(OBJECTS) -o build/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f src/*.o
	rm -rf build
