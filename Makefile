# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaeducas <gaeducas@student.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 12:37:17 by gaeducas          #+#    #+#              #
#    Updated: 2025/12/30 13:00:18 by gaeducas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## VARIABLES GÉNÉRALES
CC              = cc
CFLAGS          = -Wall -Wextra -Werror
NAME            = so_long
RM              = rm -rf

## CHEMINS
SRCS_FOLDER     = src/
LIBS_FOLDER     = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER  = objects

## BREW CONFIG (Pour Mac M2)
BREW_PREFIX     = $(shell brew --prefix)
INCLUDES_BREW  = -I$(BREW_PREFIX)/include
LIBS_BREW      = -L$(BREW_PREFIX)/lib

## BIBLIOTHÈQUES
MLX_DIR         = $(LIBS_FOLDER)MacroLibX/
LIBFT_DIR       = $(LIBS_FOLDER)libft/
FT_PRINTF_DIR   = $(LIBS_FOLDER)ft_printf/

LIBFT           = $(LIBFT_DIR)libft.a
FT_PRINTF       = $(FT_PRINTF_DIR)libftprintf.a
MLX             = $(MLX_DIR)libmlx.dylib

## FLAGS MLX POUR MAC
MLX_FLAGS       = -L$(MLX_DIR) -lmlx -framework Cocoa -framework OpenGL -framework IOKit -lSDL2

## SOURCES ET OBJETS
SRCS            = $(SRCS_FOLDER)window.c \
					$(SRCS_FOLDER)so_long.c

# On génère la liste des objets
OBJS            = $(SRCS:$(SRCS_FOLDER)%.c=$(OBJECTS_FOLDER)/%.o)

## RÈGLES PRINCIPALES
all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(LIBS_BREW) $(MLX_FLAGS) -o $(NAME)
	@install_name_tool -change libmlx.dylib $(MLX) $(NAME)

# Règle de compilation des .o
$(OBJECTS_FOLDER)/%.o: $(SRCS_FOLDER)%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES_BREW) -I $(INCLUDES_FOLDER) -I $(MLX_DIR)includes -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -c $< -o $@

## RÈGLES DES LIBS
$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR) all

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/seekrs/MacroLibX.git $(MLX_DIR); \
	fi
	@echo "Building MLX for Apple Silicon..."
	@$(MAKE) -C $(MLX_DIR) UNUSE_VULKAN=1 FETCH_OPENGL=1
## NETTOYAGE
clean:
	$(RM) $(OBJECTS_FOLDER)
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	@make -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re