/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:51 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:04:30 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		destroy_global(t_global *global);

static void	destroy_global(t_global *global)
{
	free_matrix((void ***)&global->env, 0);
	ft_free_lst(global->lst_local);
	ft_free_lst(global->lst_env);
	free_mem((void **)&global);
}

void	free_mem(void **mem)
{
	if (*mem != 0)
		free(*mem);
	*mem = 0;
}

char	**free_matrix(void ***matrix, int size)
{
	int	n;

	n = 0;
	if (*matrix != NULL)
	{
		if (size != 0)
			while (n < size)
				free_mem(&(*matrix)[n++]);
		else
			while ((*matrix)[n] != NULL)
				free_mem(&(*matrix)[n++]);
		free_mem((void **)&*matrix);
	}
	return (NULL);
}

void	free_global(t_global *global, int flag)
{
	int	n;

	n = 0;
	while (n < global->pipeline)
	{
		free_matrix((void ***)&global->tokens[n].file, 0);
		free_mem((void **)&global->tokens[n].command);
		free_matrix((void ***)&global->tokens[n].arg, 0);
		n++;
	}
	free_mem((void **)&global->tokens);
	free_mem((void **)&global->input);
	free_matrix((void ***)&global->fd, global->pipeline + 1);
	free_mem((void **)&global->pid);
	global->pipeline = 0;
	if (flag == 1)
		destroy_global(global);
}
