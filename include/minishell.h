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

//Funcion para leer de la terminal
char			*get_input(char *prompt);
//Manejador de señales para probar control+c exit (duda si hay que silenciarlo para que no muestre "C")
void			handler_signal(int signal);

#endif
