/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:43:51 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:43:52 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_and_store_history(char *input)
{
	int		fd_history;

	add_history(input);
	fd_history = open("/tmp/.bash_history", \
	O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_history == -1)
	{
		ft_putstr_fd("minishell: error openning bash history\n", 2);
		free (input);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(input, fd_history);
	ft_putchar_fd('\n', fd_history);
	close(fd_history);
}
