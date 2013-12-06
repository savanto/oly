CC = g++
CFLAGS = 

# Exclude template
SOURCES = $(filter-out template.cpp,$(wildcard *.cpp))
#OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGETS)
	rm -rf *.out
