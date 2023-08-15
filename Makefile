NAME = minishell

SRC =	src/main.c																\
		src/parser/history/bash_history.c										\
		src/parser/get_lexer/get_lexer.c										\
		src/parser/get_lexer/lexer_counter.c									\
		src/parser/get_lexer/lexer_maker.c										\
		src/parser/utils/gnl.c													\
		src/parser/utils/utils.c												\
		src/parser/expansion_variable/get_variables.c							\
		src/parser/expansion_variable/expand_variables.c						\
		src/parser/expansion_variable/replace_variables.c						\
		src/parser/expansion_variable/utils.c									\
		src/parser/get_struct/check_syntax.c									\
		src/parser/get_struct/get_struct.c										\
		src/parser/get_struct/get_tokens.c										\
		src/parser/get_struct/tokens_counter.c									\
		src/parser/get_struct/tokens_maker.c									\
		src/signals/signal.c													\
		src/parser/variables/var_environment.c									\
		src/parser/variables/var_local.c										\
		src/parser/utils/list_utils.c											\
		src/parser/utils/list_utils_2.c											\
		src/parser/variables/lexer_var_local.c		   							\
		src/parser/variables/lexer_var_local_2.c								\
		src/parser/variables/utils_var.c										\
		src/builtins/ft_pwd.c													\
		src/builtins/ft_env.c													\

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
