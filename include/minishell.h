#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
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

/*
Estructura específica para guardar los lexer $ y poder
vincularlos luego con su variable de una forma más simple.
*/

typedef struct s_lexer
{
	char		*variable;
	char		*expanded;
	int			position;
}				t_lexer;

typedef struct s_token
{
	char		**in;
	char		**out;
	char		*cmd;
	char		**arg;
	int			fd_in;
	int			fd_out;
}				t_token;

// Estructura para guardar una copia de environment a modo de diccionario y
// que nuestra mini_shell trabaje directamente con esta copia

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}					t_node;	
typedef struct s_global
{
	char		*input;
	int			exit_status;
	t_node		*lst_env;
	t_token		*tokens;
}				t_global;

//parser/history/bash_history
void		add_and_store_history(char *input);

//parser/get_lexer/lexer_counter
char		**get_lexer(char *input, t_global *global);

//parser/get_lexer/lexer_counter
void		quoted_lexer_counter(int *counter, char **s);
void		redirection_lexer_counter(int *counter, char **s);
void		words_counter(int *counter, char **s);
int			lexer_counter(char *s);

//parser/get_lexer/lexer_maker
void		quoted_lexer_splitter(int *n, char **s, char ***lexer);
void		redirection_lexer_splitter(int *n, char **s, char ***lexer);
void		words_splitter(int *n, char **s, char ***lexer);
char		**free_lexer(char **lexer);
char		**lexer_maker(char *s);

//parser/get_lexer/get_lexer
char		*expansion_variable(char *input, t_global *global);

//parser/expansion_variable/get_variables
int			variable_expansion_counter(char *input);
void		skip_quotes(char **s);
void		variable_lexer_filler(int *n, int length, char **s, t_lexer *lexer);
void		check_expansion_and_delimiters(int *n, char **s, t_lexer *lexer);
t_lexer		*get_variable_expansion_lexer(char *input);

//parser/expansion_variable/expand_variables

int			get_variable_from_path(int n, t_lexer *lexer, t_global *global);
int			get_variable_from_history(int n, t_lexer *lexer, t_global *global);
void		get_variable_expansion_value(int n, t_lexer *lexer, t_global *global);

//parser/expansion_variable/replace_variables
void		get_size_variables(int *var, int *exp, char *input, t_lexer *lexer);
char		*replace_variables(char *input, t_lexer *lexer);

//parser/expansion_variable/utils
void		read_from_history(int n, t_lexer *lexer, char *needle, int size);
t_lexer		*free_expansion_lexer(int n, t_lexer *lexer, int flag);
void		replace_function(char *new_input, char *input, t_lexer *lexer);

//parser/utils/gnl
char		*gnl(int fd);
char		*read_fd(int fd, char *static_buffer);
char		*return_line(char *static_buffer);
char		*return_static(char *static_buffer);

//parser/get_struct/get_struct
t_global	*init_struct(char **env);
void		get_struct_data(t_global *global, char *input);

//parser/get_struct/get_tokens
int			lexer_pipes_counter(char **lexer);
t_token		*get_tokens(char *input, t_global *global);

//parser/get_struct/check_syntax
int			quotes_check(char **lexer, int n);
int			pipes_and_redirections_check(char **lexer, int n);
int			next_lexer_check(char **lexer, int n);
int			syntax_error_check(char **lexer);

//parser/dictionary
void		copy_environment(t_node **lst_env, char **env);

//parser/utils list
t_node		*init_list(void);
t_node		*create_nodo(char *key, char *value);
void		insert_last(t_node **list, t_node *new_nodo);
t_node		*final(t_node *list);
void		print_stack(t_node *list);
void		ft_free_lst(t_node *lst);
int			ft_size_lst(t_node *lst);
void		error(void);
char		*search_key(t_node *lst, char *c);
int			search_key_and_replace(t_node *lst, char *key, char *val);
char		*extract_clue(char *c);
char		*extract_value(char *c);
int			local_var(char *s);

//signal
void		ft_sigint_handler(int sig);
void		ft_sigquit_handler(int sig);

//build_in
int			control_d(char *input);
#endif
