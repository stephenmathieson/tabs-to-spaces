
PREFIX ?= /usr/local

test: test.c src/tabs-to-spaces.c src/str-replace.c src/str-copy.c
	$(CC) -std=c99 $^ -o $@
	./$@

t2s: src/*.c
	$(CC) -std=c99 $^ -o $@

install: t2s
	cp -f t2s $(PREFIX)/bin/t2s

uninstall:
	rm -f $(PREFIX)/bin/t2s

.PHONY: test
