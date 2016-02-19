# Declaration of variables
CC = gcc
CFLAGS = -Wall -ggdb -std=gnu99 #enable warnings and debugging info
LDFLAGS = -pthread #here we could add dynamically linked libraries like -lrt -lm -lpthread and others

# File names
EXEC = simple
SOURCES = $(wildcard *.c)
DEPS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
