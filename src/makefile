IDIR =../lib
CC=gcc
CFLAGS= -I$(IDIR)


ODIR=obj
LDIR =../lib

LIBS=  -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lm

_DEPS = joueur.h bombe.h matriceBombe.h affichage_map.h monstre.h menu.h level.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = joueur.o bombe.o matriceBombe.o affichage_map.o monstre.o menu.o level1.o level2.o level3.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

../bin/Bomberman2D: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o *~ core $(IDIR)/*~
