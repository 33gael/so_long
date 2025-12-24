NAME		:= libftprintf.a
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f

SRCS := ft_printf.c \
		srcs/ft_putchar.c \
		srcs/ft_putnbr_hex.c \
		srcs/ft_put_ptr.c \
		srcs/ft_putnbr.c \
		srcs/ft_putnbr_unsigned.c \
		srcs/ft_putstr.c \

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
		:= rm -f
