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

int	main(void);

/*Función momentánea para liberar memoria y salir del programa. Se tendrá que ir modificando
dependiendo de la memoria alojada en el heap.
*/
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


#endif
