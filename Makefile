## VARIABLES GÉNÉRALES
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
NAME            = so_long
RM              = rm -rf

## CHEMINS
SRCS_FOLDER     = src/
LIBS_FOLDER     = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER  = objects/

## SOUS-PROJETS (BIBLIOTHÈQUES)
MLX_DIR         = $(LIBS_FOLDER)MacroLibX/
LIBFT_DIR       = $(LIBS_FOLDER)libft/
FT_PRINTF_DIR	= $(LIBS_FOLDER)ft_printf/
GNL_DIR			= $(LIBS_FOLDER)get_next_line/
MLX_HEADERS_DIR = $(MLX_DIR)includes/

# Fichiers compilés des bibliothèques [cite: 1, 2]
LIBFT           = $(LIBFT_DIR)libft.a
FT_PRINTF		= $(FT_PRINTF_DIR)libftprintf.a
MLX             = $(MLX_DIR)libmlx.so

## SOURCES ET OBJETS
# Ajoute ici tes nouveaux fichiers .c au fur et à mesure
SRCS            = $(SRCS_FOLDER)window.c \
					$(SRCS_FOLDER)so_long.c

# Transformation des chemins pour les objets [cite: 1]
OBJS            = $(patsubst $(SRCS_FOLDER)%.c, $(OBJECTS_FOLDER)%.o, $(SRCS))

## RÈGLES PRINCIPALES
all: $(NAME)

# 1. LIEN FINAL (Correction : Ajout de FT_PRINTF et ordre des libs) 
$(NAME): $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX) -lSDL2 -lm -o $(NAME)

# 2. COMPILATION DES OBJETS (Correction : Ajout des -I pour les headers) 
$(OBJECTS_FOLDER)%.o: $(SRCS_FOLDER)%.c | $(OBJECTS_FOLDER)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -I $(MLX_HEADERS_DIR) -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -c $< -o $@

# Création du dossier d'objets si inexistant 
$(OBJECTS_FOLDER):
	@mkdir -p $(OBJECTS_FOLDER)

## 3. RÈGLES DES BIBLIOTHÈQUES

$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR) all

$(FT_PRINTF):
	@echo "Compiling Ft_printf..."
	@make -C $(FT_PRINTF_DIR) all

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MacroLibX..."; \
		git clone https://github.com/seekrs/MacroLibX.git $(MLX_DIR); \
	fi

$(MLX): $(MLX_DIR)
	@echo "Compiling MacroLibX..."
	@make -C $(MLX_DIR) -j

## NETTOYAGE
clean:
	@echo "Cleaning objects..."
	$(RM) $(OBJECTS_FOLDER)
	@make -C $(LIBFT_DIR) clean || true
	@make -C $(FT_PRINTF_DIR) clean || true
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean || true; fi

fclean: clean
	@echo "Full cleaning..."
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean || true
	@make -C $(FT_PRINTF_DIR) fclean || true
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) fclean || true; fi

re: fclean all

.PHONY: all clean fclean re