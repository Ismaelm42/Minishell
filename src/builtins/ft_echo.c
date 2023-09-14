/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:40:02 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:40:05 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_global *g, int n)
{
	int	i;

	i = -1;
	if (!g->tokens[n].arg[0])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		free_global(g, 1);
		exit(0);
	}
	else if (ft_strncmp(g->tokens[n].arg[0], "-n", 3) == 0)
		i++;
	while (g->tokens[n].arg[++i])
	{	
		ft_putstr_fd(g->tokens[n].arg[i], STDOUT_FILENO);
		if (g->tokens[n].arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (ft_strncmp(g->tokens[n].arg[0], "-n", 3) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
