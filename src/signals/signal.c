#include "../../include/minishell.h"
/*
ctrl C && ctrl D & ctrl \ (linux ctrl + } usar en terminal en la de 
Visual no va demasiado bien) -> DEBERAN DE FUNCIONAR COMO EN BASH

CUANDO SEA INTERACTIVO:( prompt a la espera de commandosn )

ctrl-C imprime una nueva entrada en una línea nueva.
ctrl-D termina el shell.
ctrl-\ no hace nada.
*/
int	control_d(t_global *g, char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		free_global(g, 1);
		exit (0);
	}
	return (1);
}

/*
Manejador de señal SIGINT de forma interactiva
*/
void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		signal(SIGINT, ft_sigint_handler);
	}
}

/*
Manejador de señales para procesos trata la señal recibida 
y dependiendo de la que reciba actua de una forma u otra
*/
void	ft_sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;

		ft_putstr_fd("\n", STDOUT_FILENO);
		signal(SIGINT, ft_sigint_proc);
	}
	else if (sig == SIGQUIT)
	{
		//ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		signal(SIGQUIT, ft_sigint_proc);
	}
}
void	ft_sigint_heredoc(int sig)
{
	//ioctl(0, TIOCSTI, "\n"); 
	//ft_putstr_fd("CABEZA\n", STDOUT_FILENO);
	// ft_putstr_fd("\n", STDOUT_FILENO);
	// rl_on_new_line();
	(void)sig;
	exit(130);
}

// void	handler_prueba(int signal)
// {
// 	if (signal == SIGINT || signal == SIGQUIT)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// }
