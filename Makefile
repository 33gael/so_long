## VARIABLES GÉNÉRALES
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long
RM = rm -rf

## CHEMINS
SRCS_FOLDER = src/
LIBS_FOLDER = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER = objects/

## SOUS-PROJETS (BIBLIOTHÈQUES)
MLX_DIR = $(LIBS_FOLDER)MacroLibX/
LIBFT_DIR = $(LIBS_FOLDER)libft/
MLX_HEADERS_DIR = $(MLX_DIR)includes/  # Nouveau : Chemin vers les headers MLX

## SOURCES ET OBJETS PRINCIPAUX
# Liste des fichiers sources du projet so_long
SRCS = $(SRCS_FOLDER)window.c \
		$(SRCS_FOLDER)main.c \
		
SRCS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(notdir $(SRCS:.c=.o)))

## RÈGLE PRINCIPALE
all: $(NAME)

## 1. RÈGLE DE LIEN FINAL
$(NAME): $(SRCS_OBJS) $(LIBFT_DIR)libft.a $(MLX_DIR)libmlx.so
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $^ -lSDL2 -lm -o $@

## 2. RÈGLE DE COMPILATION DES OBJETS PRINCIPAUX
# Dépend du dossier MLX pour s'assurer que les en-têtes sont clonés
$(OBJECTS_FOLDER)%.o: $(SRCS_FOLDER)%.c | $(MLX_DIR)
	@mkdir -p $(dir $@)
    # Ajout de -I $(MLX_HEADERS_DIR) ici
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -I $(MLX_HEADERS_DIR) -c $< -o $@

## 3. RÈGLES DES SOUS-PROJETS

# --- Libft ---
$(LIBFT_DIR)libft.a:
	@echo "Compiling Libft..."
	make -C $(LIBFT_DIR) all

# --- MacroLibX Clone (Dépendance pour les .o) ---
# Règle pour créer le dossier MLX et cloner le repo
$(MLX_DIR):
	@echo "Cloning MacroLibX..."
	git clone https://github.com/seekrs/MacroLibX.git $(MLX_DIR)

# --- MacroLibX Compile (Dépendance pour le Link) ---
# La bibliothèque libmlx.so dépend du dossier MLX (pour s'assurer qu'il est cloné)
$(MLX_DIR)libmlx.so: $(MLX_DIR)
	@echo "Compiling MacroLibX..."
	make -C $(MLX_DIR) -j

## RÈGLES DE NETTOYAGE
clean:
	@echo "Cleaning objects..."
	$(RM) $(OBJECTS_FOLDER)
	@echo "Cleaning Libft objects..."
	make -C $(LIBFT_DIR) clean || true
	@echo "Cleaning MacroLibX objects..."
	make -C $(MLX_DIR) clean || true

fclean: clean
	@echo "Full cleaning..."
	$(RM) $(NAME)
	@echo "Cleaning Libft executable/library..."
	make -C $(LIBFT_DIR) fclean || true
	@echo "Cleaning MacroLibX executable/library..."
	make -C $(MLX_DIR) fclean || true
	@echo "Removing MacroLibX folder..."
	$(RM) $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re