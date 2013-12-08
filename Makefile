CC = g++
CFLAGS = 

# Exclude template
SOURCES = $(filter-out template.cpp,$(wildcard *.cpp))
#OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = $(SOURCES:.cpp=)

all: $(TARGETS)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

new: template.cpp
ifndef PROGRAM
	$(error use "make new PROGRAM=<program-name>")
endif
	@cat $< | sed 's/PROGRAM/$(PROGRAM)/g' > $(PROGRAM).cpp
	@echo "Initialized new program '$(PROGRAM)' from template in $(PROGRAM).cpp"

clean:
	rm -rf $(TARGETS)
	rm -rf *.out
