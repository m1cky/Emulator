CC ?= gcc
CFLAGS=
export CFLAGS
LDFLAGS=
export LDFLAGS
SOURCES=main.c
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