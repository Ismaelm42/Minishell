#include "../../include/minishell.h"

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

void	ft_sigint_handler(int sig)
{
	(void)sig;

	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, ft_sigint_handler);
}

void	ft_sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		signal(SIGINT, ft_sigint_proc);
	}
}
