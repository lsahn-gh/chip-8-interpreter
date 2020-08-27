
CFLAGS=-g -I./
LDFLAGS=
TARGET=main

SOURCES = $(shell find . -name "*.c")
OBJS = $(SOURCES:.c=.o)

.PHONY: all
all: ${TARGET}

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	-$(RM) $(TARGET) $(OBJS)
