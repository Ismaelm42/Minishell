NAME = minishell

SRC =	src/main.c							\
		src/parser/token_counter.c			\
		src/parser/token_maker.c			\
		src/parser/gnl.c					\
		src/parser/variable_expansion.c		\
											\
											\
											\
											\
											\
											\
											\

OBJT_DIR = objt

OBJT = $(addprefix $(OBJT_DIR)/, $(patsubst %.c, %.o, $(SRC)))

LIBFT = libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAKEFLAGS += --quiet

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) $(OBJT) $(LIBFT) -o $(NAME) -lreadline

$(OBJT_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJT_DIR)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
