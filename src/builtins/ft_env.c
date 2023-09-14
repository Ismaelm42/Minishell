/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:40:15 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:40:17 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i] != NULL)
	{
		ft_putstr_fd(g->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
