/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:52:03 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:14:15 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_node	*init_list(void)
{
	return (NULL);
}

t_node	*create_nodo(char *key, char *value)
{
	t_node	*aux;

	aux = (t_node *)malloc(sizeof(t_node));
	aux->key = key;
	aux->value = value;
	aux->next = NULL;
	return (aux);
}

void	insert_last(t_node **list, t_node *new_nodo)
{
	t_node	*aux;

	if (*list)
	{
		aux = final(*list);
		aux -> next = new_nodo;
		new_nodo -> next = NULL;
	}
	else
		*list = new_nodo;
}

t_node	*final(t_node *list)
{
	t_node	*aux;

	aux = list;
	if (!list)
		return (NULL);
	while (aux && aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	print_stack(t_node *list)
{
	t_node	*aux;

	aux = list;
	while (aux != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(aux->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putstr_fd(aux->value, STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		aux = aux -> next;
	}	
}
