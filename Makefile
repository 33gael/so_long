CC              = cc
CFLAGS          = -Wall -Wextra -Werror
NAME            = so_long
RM              = rm -rf

SRCS_FOLDER     = src/
UTILS_FOLDER	= src/utils/
LIBS_FOLDER     = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER  = objects/

MLX_DIR         = $(LIBS_FOLDER)MacroLibX/
LIBFT_DIR       = $(LIBS_FOLDER)libft/
FT_PRINTF_DIR	= $(LIBS_FOLDER)ft_printf/
GNL_DIR			= $(LIBS_FOLDER)get_next_line/*.c
MLX_HEADERS_DIR = $(MLX_DIR)includes/

LIBFT           = $(LIBFT_DIR)libft.a
FT_PRINTF		= $(FT_PRINTF_DIR)libftprintf.a
MLX             = $(MLX_DIR)libmlx.so

SRCS            = $(SRCS_FOLDER)so_long.c \
					$(UTILS_FOLDER)utils_win.c \
					$(SRCS_FOLDER)map_parsing.c \
					$(SRCS_FOLDER)init_img.c \
					$(SRCS_FOLDER)render_map.c \
					$(SRCS_FOLDER)moves.c \
					$(SRCS_FOLDER)map_check.c \
					$(SRCS_FOLDER)map_path.c \
					$(SRCS_FOLDER)map_check_2.c \

OBJS            = $(patsubst $(SRCS_FOLDER)%.c $(UTILS_FOLDER)%.c, $(OBJECTS_FOLDER)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL_DIR) $(MLX) -lSDL2 -lm -o $(NAME)

$(OBJECTS_FOLDER)%.o: $(SRCS_FOLDER)%.c | $(OBJECTS_FOLDER)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -I $(MLX_HEADERS_DIR) -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -c $< -o $@

$(OBJECTS_FOLDER):
	@mkdir -p $(OBJECTS_FOLDER)


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

clean:
	@echo "Cleaning objects..."
	$(RM) $(OBJECTS_FOLDER)
	@make -C $(LIBFT_DIR) clean || true
	@make -C $(FT_PRINTF_DIR) clean || true
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean || true; fi

fclean: clean
	@echo "Full cleaning..."
	$(RM) $(NAME) $(MLX_DIR)
	@make -C $(LIBFT_DIR) fclean || true
	@make -C $(FT_PRINTF_DIR) fclean || true
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) fclean || true; fi

re: fclean all

.PHONY: all clean fclean re