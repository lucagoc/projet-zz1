# Variables
CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_imagean -lm
OBJ = anime_sprite.o pave_serpent_saim.o x_fenetre_saim.o

# Cibles
all: anime pave fenetre

anime: anime_sprite.o
	$(CC) $(CFLAGS) -o anime anime_sprite.o $(LDFLAGS)

pave: pave_serpent_saim.o
	$(CC) $(CFLAGS) -o pave pave_serpent_saim.o $(LDFLAGS)

fenetre: x_fenetre_saim.o
	$(CC) $(CFLAGS) -o fenetre x_fenetre_saim.o $(LDFLAGS)

# Compilation des fichiers objets
anime_sprite.o: anime_sprite.c
	$(CC) $(CFLAGS) -c anime_sprite.c

pave_serpent_saim.o: pave_serpent_saim.c pave_serpent_saim.h
	$(CC) $(CFLAGS) -c pave_serpent_saim.c

x_fenetre_saim.o: x_fenetre_saim.c
	$(CC) $(CFLAGS) -c x_fenetre_saim.c

# Règle de nettoyage
clean:
	rm -f $(OBJ) anime pave fenetre

.PHONY: all clean
