/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:42:10 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:42:11 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**search_next_file(char **files, char *redir)
{
	int	i;

	i = 0;
	while (files[i] != NULL
		&& ft_strncmp(files[i], redir, ft_strlen(redir) + 1) != 0)
		i++;
	if (files[i] != NULL)
		i++;
	return (&files[i]);
}

void	access_error_message(char *error, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(message, 2);
}

void	fd_closer(int **fd, int pipeline, int n)
{
	int		i;

	i = 0;
	while (i < pipeline + 1)
	{
		if (i != n)
			close(fd[i][0]);
		if (i != n + 1)
			close(fd[i][1]);
		i++;
	}
}

void	exit_child_process(t_global *global, char **array, char *str, int stat)
{
	free_mem((void **)&str);
	free_matrix((void ***)&array, 0);
	free_global(global, 1);
	exit(stat);
}

void	print_error(char *message, int code_error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(code_error), 2);
	ft_putstr_fd("\n", 2);
}
