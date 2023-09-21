/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:21 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/21 10:38:50 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_key(char *key, int flag)
{
	int	i;

	i = 0;
	if (ft_isalpha(((int)key[i])) || key[i] == '_')
	{	
		i++;
		while (key[i] != '\0' && (ft_isalnum(key[i]) || key[i] == '_'))
			i++;
	}
	if (key[i] != '\0' || key[i] == ' ')
	{
		if (flag == 1)
			free_mem((void **)&key);
		return (1);
	}
	else
	{
		if (flag == 1)
			free_mem((void **)&key);
	}
	return (0);
}

int	search_key_and_delete(t_node **lst, char *key)
{
	t_node	*aux;
	t_node	*aux_prev;

	aux = *lst;
	aux_prev = NULL;
	while (aux && ft_strncmp(aux->key, key, (ft_strlen(key) + 1)) != 0)
	{
		aux_prev = aux;
		aux = aux->next;
	}
	if (aux == NULL)
		return (1);
	else
	{
		if (aux == *lst)
			*lst = aux ->next;
		else
			aux_prev->next = aux->next;
		aux->next = NULL;
		ft_free_lst(aux);
	}
	return (0);
}
