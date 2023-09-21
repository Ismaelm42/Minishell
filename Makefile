# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 15:52:51 by Jroldan-          #+#    #+#              #
#    Updated: 2023/09/21 11:28:23 by Jroldan-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/builtins/ft_env.c									\
		src/builtins/ft_export.c								\
		src/builtins/ft_pwd.c									\
		src/builtins/ft_unset.c									\
		src/builtins/ft_echo.c									\
		src/builtins/ft_cd.c									\
		src/builtins/ft_exit.c									\
		src/builtins/utils_builtins.c							\
		src/exec/execute_commands.c								\
		src/exec/get_command.c									\
		src/exec/files.c										\
		src/exec/heredocs.c										\
		src/exec/utils.c										\
		src/history/bash_history.c								\
		src/main/main.c											\
		src/parser/expansion_variable/expand_variables.c		\
		src/parser/expansion_variable/get_variables.c			\
		src/parser/expansion_variable/pid_variable.c			\
		src/parser/expansion_variable/replace_variables.c		\
		src/parser/expansion_variable/utils.c					\
		src/parser/get_lexer/get_lexer.c						\
		src/parser/get_lexer/lexer_counter.c					\
		src/parser/get_lexer/lexer_maker.c						\
		src/parser/get_lexer/utils.c							\
		src/parser/get_struct/check_syntax.c					\
		src/parser/get_struct/get_struct.c						\
		src/parser/get_struct/get_tokens.c						\
		src/parser/get_struct/tokens_counter.c					\
		src/parser/get_struct/tokens_maker.c					\
		src/parser/variables/lexer_var_local_2.c				\
		src/parser/variables/lexer_var_local.c					\
		src/parser/variables/var_environment.c					\
		src/parser/variables/var_local.c						\
		src/prompt/readline_prompt.c							\
		src/signals/signal.c									\
		src/signals/utils_signal.c								\
		src/utils/clean_utils/clean.c							\
		src/utils/list_utils/list_utils_2.c						\
		src/utils/list_utils/list_utils.c						\
		src/utils/list_utils/utils_var_2.c						\
		src/utils/list_utils/utils_var.c						\
		src/wildcards/utils.c									\
		src/wildcards/wildcards_counter.c						\
		src/wildcards/wildcards.c								\


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
