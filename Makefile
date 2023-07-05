NAME =	minishell

SRC =	main.c	\
				\
				\
				\
				\
				\
				\
				\
				\
				\

OBJT = $(SRC:.c=.o)

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

MAKEFLAGS += --quiet

all: $(LIBFT) $(NAME)
	$(MAKE) clean
#eliminar para la corrección

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(OBJT)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o ${NAME} -lreadline

clean:
	$(RM) $(OBJT)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY : all clean fclean re
