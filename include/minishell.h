/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:37:56 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:24:59 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_lexer
{
	char			*input;
	char			*variable;
	char			*expanded;
	int				position;
}				t_lexer;

typedef struct s_token
{
	char			*command;
	char			**arg;
	char			**file;
}				t_token;

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_global
{
	char			*input;
	char			**env;
	int				**fd;
	int				pipeline;
	int				exit_status;
	pid_t			*pid;
	struct termios	prompt;
	t_node			*lst_env;
	t_node			*lst_local;
	t_token			*tokens;
}				t_global;

extern int			g_flag_exit_status;

//parser/history/bash_history
void		add_and_store_history(char *input);

//parser/get_lexer/lexer_counter
int			lexer_counter(char *s);

//parser/get_lexer/lexer_maker
char		**lexer_maker(char *s);

//parser/get_lexer/utils
char		reject_quotes(char *s, char *substr, int *i, int *j);
void		check_quotes(char *s, int *length);

//parser/get_lexer/get_lexer
char		**get_lexer(char *input, t_global *global);

//parser/expansion_variable/get_variables
int			variable_expansion_counter(char *input);
t_lexer		*get_variable_expansion_lexer(char *input);

//parser/expansion_variable/expand_variables
char		*expansion_variable(char *input, t_global *global);

//parser/expansion_variable/replace_variables
char		*replace_variables(char *input, t_lexer *lexer);

//parser/expansion_variable/utils
t_lexer		*create_expansion_lexer_struct(char *input, int size);
void		handle_edge_cases(char **input, int *counter);
void		skip_quotes(char **s, int *lock);
int			check_edge_cases(char *s);
t_lexer		*free_expansion_lexer(t_lexer *lexer, int flag);




/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//parser/expansion_variable/pid_variable
void		pid_child_process(t_global *pid_global, int n);
char		*pid_parent_process(t_global *pid_global, int n);
char		*get_pid_process(t_global *global);
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////




//parser/get_struct/check_syntax
int			syntax_error_check(char **lexer);

//parser/get_struct/get_struct
t_global	*init_struct(char **env);
void		get_struct_data(t_global *global, char *input);

//src/parser/get_struct/get_tokens
int			get_tokens(char *input, t_global *global);

//src/parser/get_struct/tokens_counter
int			lexer_pipes_counter(char **lexer);
int			*token_counter(char **lexer);

//src/parser/get_struct/tokens_maker
void		allocate_token_memory(t_token *tokens, int *size);
void		token_filler(t_token *tokens, char **lexer);
void		advance_lexer_tokens(char ***lexer, t_token **tokens);

//parser/var_environment
char		**copy_environment(char **env);
int			search_env(char *var, char **env);
char		*search_env_expand(char *var, char **envp);
int			search_env_replace(char *var, char *val, char **envp, int flag);
void		add_env(char ***env, char *argv);

//parser/variables
int			local_var(t_global *g, char *input);
char		*extract_clue(char *c);
char		*extract_value(char *c);
char		*search_key(t_node *lst, char *key);
int			search_key_and_replace(t_node *lst, char *key, char *val, int flag);
int			search_key_and_delete(t_node **lst, char *key);
void		var_quoted_lexer_splitter(int *n, char **s, char ***lexer);
void		var_words_splitter(int *n, char **s, char ***lexer);
char		**var_lexer_maker(char *s);
int			var_lexer_counter(char *s);
void		put_dictionary_local(char *nv, t_global *g);
int			check_key(char *key, int flag);

//parser/utils
void		free_mem(void **mem);
char		**free_matrix(void ***matrix, int size);
void		free_global(t_global *global, int flag);

//parser/utils/list_utils
t_node		*init_list(void);
t_node		*create_nodo(char *key, char *value);
void		insert_last(t_node **list, t_node *new_nodo);
t_node		*final(t_node *list);
void		print_stack(t_node *list);
void		copy_environment_list(t_node **lst_env, char **env);
void		ft_envlst_short(t_node **lst);

//parser/utils/list_utils_2
void		ft_free_lst(t_node *lst);

//prompt/readline_prompt
char		*readline_prompt(void);

//signals/signals
void		ft_sigint_handler(int sig);
void		ft_sig_proc(int sig);
void		ft_sigint_heredoc(int sig);
void		ft_sigint_open_pipe(int sig);
int			control_d(t_global *g, char *input);

//signals/utils_signals
void		exit_status_flag(t_global *global);

//exec/execute_commands
int			create_pipes_and_pid(t_global *global);
int			execute_commands(t_global *global);

//exec/files
void		handle_files(t_global *global, int n);

//exec/heredoc
int			process_heredocs(t_global *global);

//exec/get_command
char		**get_exec_command(t_global *global, int n);

//exec/utils
char		**search_next_file(char **files, char *redir);
void		access_error_message(char *error, char *message);
void		exit_child_process(t_global *global, char **array, \
			char *str, int stat);
void		fd_closer(int **fd, int pipeline, int n);
void		print_error(char *message, int code_error);

//build_in

void		ft_pwd(void);
void		ft_env(t_global *g);
void		ft_export(t_global *g, int n);
void		ft_echo(t_global *g, int n);
void		ft_cd(t_global *g, int n);
void		action_export(t_global *g, int n, int i);
void		ft_unset(t_global *g, int n);
void		ft_exit(t_global *g, int n);
int			check_edge_builtins(t_global *global);
char		**check_builtins(t_global *g, int n);
void		builtins(t_global *g, int n);

#endif
