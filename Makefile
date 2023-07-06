NAME = minishell

OBJT_DIR = objt

SRC =	src/main.c				\
		src/parser/parsing.c	\
								\
								\
								\
								\
								\
								\
								\
								\
								\
								\

OBJT = $(addprefix $(OBJT_DIR)/, $(patsubst %.c, %.o, $(SRC)))

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) $(OBJT) $(LIBFT) -o $(NAME) -lreadline

$(OBJT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJT_DIR)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
