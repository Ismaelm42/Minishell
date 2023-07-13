NAME = minishell

SRC =	src/main.c																\
		src/parser/get_tokens/token_counter.c									\
		src/parser/get_tokens/token_maker.c										\
		src/parser/utils/gnl.c													\
		src/parser/expansion_variable/get_variables.c							\
		src/parser/expansion_variable/expand_variables.c						\
		src/parser/expansion_variable/replace_variables.c						\
		src/parser/expansion_variable/utils.c									\
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
