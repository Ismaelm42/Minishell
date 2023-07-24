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

//parser/history/bash_history
void		add_and_store_history(char *input);

//parser/get_lexer/lexer_counter
char		**get_lexer(char *input);

//parser/get_lexer/lexer_counter
void		quoted_lexer_counter(int *counter, char **s);
void		redirection_lexer_counter(int *counter, char **s);
void		words_counter(int *counter, char **s);
int			lexer_counter(char *s);

//parser/get_lexer/lexer_maker
void		quoted_lexer_splitter(int *n, char **s, char ***lexer);
void		redirection_lexer_splitter(int *n, char **s, char ***lexer);
void		words_splitter(int *n, char **s, char ***lexer);
char		**free_lexer(int n, char **lexer);
char		**lexer_maker(char *s);

//parser/get_lexer/get_lexer
char		*expansion_variable(char *input);

//parser/expansion_variable/get_variables
int			variable_expansion_counter(char *input);
void		skip_quotes(char **s);
void		variable_lexer_filler(int *n, int length, char **s, t_lexer *lexer);
void		check_expansion_and_delimiters(int *n, char **s, t_lexer *lexer);
t_lexer		*get_variable_expansion_lexer(char *input);

//parser/expansion_variable/expand_variables

int			get_variable_from_path(int n, t_lexer *lexer);
int			get_variable_from_history(int n, t_lexer *lexer);
void		get_variable_expansion_value(int n, t_lexer *lexer);

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

#endif
