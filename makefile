.PHONY: all clean purge

CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC_DIR = src

TXT_TARGET = txtHilbert.exe
SVG_TARGET = svgMaker.exe

TXT_SRC = $(SRC_DIR)/cur.c
SVG_SRC = $(SRC_DIR)/svg.c

all: $(TXT_TARGET) $(SVG_TARGET)

$(TXT_TARGET): $(TXT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(SVG_TARGET): $(SVG_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TXT_TARGET) $(SVG_TARGET) *.o

purge: clean
	rm -f *.txt *.svg