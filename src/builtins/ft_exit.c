/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:40:44 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/21 16:55:57 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		is_param_digit(t_global *g, int n, int j);
static void		ft_exit_more_params(t_global *g, int n);

static int	is_param_digit(t_global *g, int n, int j)
{
	int	i;

	i = 0;
	if (g->tokens[n].arg[j][i] == '+' || g->tokens[n].arg[j][i] == '-')
		i++;
	while (ft_isdigit(g->tokens[n].arg[j][i]) == 1
			&& g->tokens[n].arg[0][i] != '\0')
			i++;
	if (g->tokens[n].arg[j][i] == '\0')
		return (0);
	return (1);
}

static void	ft_exit_more_params(t_global *g, int n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(g->tokens[n].command, 2);
	ft_putstr_fd(": ", 2);
	if (is_param_digit(g, n, 0) == 0)
	{
		ft_putstr_fd("too many arguments\n", 2);
		g->exit_status = 1;
	}	
	else
	{
		ft_putstr_fd(g->tokens[n].arg[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_global(g, 1);
		exit (255);
	}	
}

void	ft_exit(t_global *g, int n)
{
	int	arg;

	if (g->tokens[n].arg[0] != NULL && g->tokens[n].arg[1] != NULL)
		ft_exit_more_params(g, n);
	else if (g->tokens[n].arg[0] != NULL)
	{
		if (is_param_digit(g, n, 0) == 0)
		{
			arg = ft_atoi(g->tokens[n].arg[0]);
			free_global(g, 1);
			exit(arg);
		}
		else
		{
			ft_putstr_fd("minishell: numeric argument required\n", 2);
			free_global(g, 1);
			exit (255);
		}
	}
	else
	{
		free_global(g, 1);
		exit(0);
	}	
}
