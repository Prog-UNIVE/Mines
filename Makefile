CC=gcc
CFLAGS=-Wall -pedantic -std=gnu89 -I.

ODIR=obj
LIBS=-lm

_OBJ = slist.o queue.o stack.o matrix.o mines.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

minesweeper: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core ./*~
