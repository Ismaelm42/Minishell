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
Estructura específica para guardar los tokens $ y poder
vincularlos luego con su variable de una forma más simple.
*/
typedef struct s_tokens
{
	char	*variable;
	char	*expanded;
}			t_tokens;

//src
void		clean_up_and_exit(int status, char *ptr);
int			add_and_store_history(char *input);

//parser/token_counter
void		quoted_token_counter(int *counter, char **s);
void		redirection_token_counter(int *counter, char **s);
void		words_counter(int *counter, char **s);
int			token_counter(char *s);

//parser/token_maker
void		quoted_token_splitter(int *n, char **s, char ***tokens);
void		redirection_token_splitter(int *n, char **s, char ***tokens);
void		words_splitter(int *n, char **s, char ***tokens);
char		**free_tokens(int n, char **tokens);
char		**token_maker(char *s);

//parser/get_variables_expansion
int			variable_expansion_counter(char *input);
void		skip_quotes(char **s);


// void		tokens_filler(int *n, char **s, char ***tokens);
// char		**variable_expansion_tokens(char *input);

void		tokens_filler(int *n, char **s, t_tokens *tokens);
t_tokens	*variable_expansion_tokens(char *input);

//parser/gnl
char		*gnl(int fd);
char		*read_fd(int fd, char *static_buffer);
char		*return_line(char *static_buffer);
char		*return_static(char *static_buffer);

#endif
