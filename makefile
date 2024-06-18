# Définir les répertoires
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj

# Définir les fichiers sources et objets
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nom de l'exécutable
EXEC := $(BIN_DIR)/mana

# Compilateur et options de compilation
CC := gcc
CFLAGS := -Wall -Wextra -I$(SRC_DIR)
LIBS := -lm -lSDL2 -lSDL2_image -lSDL2_ttf

# Cible par défaut
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LIBS)

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

# Règle pour nettoyer le projet
clean:
	rm -rf $(BUILD_DIR)

# Règle pour lancer l'exécutable
run: $(EXEC)
	$(EXEC)