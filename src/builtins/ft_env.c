/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:40:15 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/17 00:27:21 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i] != NULL)
	{	
		if (strncmp(g->env[i], "_=env", 6) == 0)
			ft_putstr_fd("_=/usr/bin/env", STDOUT_FILENO);
		else
			ft_putstr_fd(g->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
