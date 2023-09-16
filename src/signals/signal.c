/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:10 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/17 00:26:46 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_sig_proc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_flag_exit_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_flag_exit_status = 2;
	}
}

void	ft_sigint_heredoc(int sig)
{
	(void)sig;
	exit(1);
}
