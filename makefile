CC ?= g++
CFLAGS+= -g -I/usr/include/SDL -lSDL_mixer
export CFLAGS
LDFLAGS= -lstdc++ -lSDL
export LDFLAGS
SOURCES=main.cc
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE ?= Pri

# Compile if sources change
.PHONY: Objects
Objects: $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES)

# Create executable if object files or exectuable name change
Pri: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

all: Objects

install: Pri

# Cleanup
.PHONY: clean
clean:
	rm -f *~ *.o