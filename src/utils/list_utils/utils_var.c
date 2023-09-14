/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:43 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:58:14 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*extract_clue(char *c)
{
	char	*position;
	char	*aux;
	size_t	i;

	aux = c;
	i = 0;
	position = ft_strchr(c, 61);
	while (aux != position)
	{
		aux++;
		i++;
	}
	return (ft_substr(c, 0, i, 0));
}

char	*extract_value(char *c)
{
	char	*position;

	position = ft_strchr(c, 61);
	while (c != position && c != NULL)
		c++;
	return (ft_substr(c, 1, ft_strlen(c), 0));
}

char	*search_key(t_node *lst, char *key)
{
	t_node	*aux;

	aux = lst;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key) + 1) == 0)
			return (aux->value);
		else
			aux = aux->next;
	}
	return (NULL);
}

int	search_key_and_replace(t_node *lst, char *key, char *val, int flag)
{
	t_node	*aux;

	aux = lst;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key) + 1) == 0)
		{
			if (flag == 1)
				free_mem((void **)&key);
			free_mem((void **)&aux->value);
			aux->value = val;
			return (0);
		}
		else
			aux = aux->next;
	}
	if (flag == 1)
	{
		free_mem((void **)&key);
		free_mem((void **)&val);
	}
	return (-1);
}

void	put_dictionary_local(char *nv, t_global *g)
{
	char	*key;
	t_node	*aux;

	key = extract_clue(g->input);
	if (search_key_and_replace(g->lst_local, key, nv, 0) != 0)
	{
		aux = create_nodo(key, nv);
		insert_last(&(g)->lst_local, aux);
	}
	else
		free_mem((void **)&key);
}
