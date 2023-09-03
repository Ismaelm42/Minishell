#include "../../include/minishell.h"

int	control_d(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	return (1);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;

	rl_redisplay();//actualiza linea de entrada en la pantalla
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);//Reemplaza la línea actualmente ingresada por una nueva línea.
	rl_on_new_line();//Realiza tareas de limpieza y reconfiguración después de que el usuario presiona Enter.
	rl_redisplay();// Actualiza la línea de entrada en la pantalla.
}
 //BASH TERMINA EL PROCESO 
// void	ft_sigquit_handler(int sig) 
// {
// 	(void)sig;
// }
