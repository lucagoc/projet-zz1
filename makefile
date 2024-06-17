# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -g

# Bibliotheques
LIBS = -lSDL2 -lm

# Liste des fichiers source
SRCS = main.c window_go_round.c window_render.c

# Liste des fichiers objet générés à partir des fichiers source
OBJS = $(SRCS:.c=.o)

# Nom de l'exécutable
TARGET = main

# Règle par défaut
all: $(TARGET)

# Règle de compilation des fichiers source en fichiers objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Règle de nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)