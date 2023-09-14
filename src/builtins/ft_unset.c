/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:13 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:40:44 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	delete_var_env(char ***env, char *key);

static void	delete_var_env(char ***env, char *key)
{
	char	**env_cp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (search_env(key, *env) == 0)
	{
		while ((*env)[i])
			i++;
		env_cp = ft_calloc(sizeof(char *), i + 1);
		i = 0;
		while ((*env)[i])
		{
			if (ft_strncmp(key, (*env)[i], ft_strlen(key)))
			{
				env_cp[j] = ft_strdup((*env)[i]);
				j++;
			}
			i++;
		}
		free_matrix((void ***)env, 0);
		*env = env_cp;
	}
}

void	ft_unset(t_global *g, int n)
{
	int	i;

	i = 0;
	if (!g->tokens[n].arg[0])
		exit (0);
	else
	{
		while (g->tokens[n].arg[i] != NULL)
		{
			search_key_and_delete(&g->lst_env, g->tokens[n].arg[i]);
			delete_var_env(&g->env, g->tokens[n].arg[i]);
			i++;
		}
	}
}
