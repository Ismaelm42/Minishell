/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:02 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:41:03 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
		ft_putstr_fd("minishell: pwd error\n", 2);
	else
	{
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free_mem((void **)&dir);
	}
}
