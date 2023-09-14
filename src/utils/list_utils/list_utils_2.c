/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:51:21 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:51:22 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_free_lst(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free_mem((void **)&tmp->key);
		free_mem((void **)&tmp->value);
		free_mem((void **)&tmp);
	}
}

void	ft_envlst_short(t_node **lst)
{
	int			diff;
	char		*change_key;
	char		*change_val;
	t_node		*tmp;

	tmp = *lst;
	if (!*lst)
		return ;
	while (tmp->next)
	{
		diff = ft_strncmp(tmp->key, tmp->next->key, 20);
		if (diff > 0)
		{
			change_key = tmp->key;
			change_val = tmp->value;
			tmp->key = tmp->next->key;
			tmp->value = tmp->next->value;
			tmp->next->key = change_key;
			tmp->next->value = change_val;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}

void	copy_environment_list(t_node **lst_env, char **env)
{
	int		i;
	t_node	*aux;

	i = 0;
	while (env[i] != NULL)
	{
		aux = create_nodo(extract_clue(env[i]), extract_value(env[i]));
		insert_last(lst_env, aux);
		i++;
	}
}
