
CC ?= gcc

PREFIX ?= /usr/local
BIN    ?= t2s

SRC  = $(wildcard src/*.c)
SRC += $(wildcard deps/*/*.c)
OBJS = $(filter-out src/main.o, $(SRC:.c=.o))

CFLAGS = -std=c99 -Wall -Wextra -Ideps

test: test.c $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)
	./test

$(BIN): src/main.o $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)


install: $(BIN)
	cp -f $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

.PHONY: test clean install uninstall
