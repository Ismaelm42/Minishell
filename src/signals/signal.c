#include "../../include/minishell.h"

void	exit_status_flag(t_global *global)
{
	if (g_flag_exit_status == 1)
		global->exit_status = 1;
	else if (g_flag_exit_status == 2)
		global->exit_status = 131;
	g_flag_exit_status = 0;
}

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
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_flag_exit_status = 1;
	}
}

void	ft_sigint_open_pipe(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		g_flag_exit_status = 1;
	}
}

void	ft_sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		signal(SIGINT, ft_sigint_proc);
		g_flag_exit_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		signal(SIGQUIT, ft_sigint_proc);
		g_flag_exit_status = 2;
	}
}

void	ft_sigint_heredoc(int sig)
{
	(void)sig;
	exit(1);
}
