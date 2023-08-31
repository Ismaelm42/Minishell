#include "../../../include/minishell.h"

//Función que chequea sintacticamente la clave (ARG) 

int	check_key(char *key, int wall)
{
	int	i;

	i = 0;
	if (ft_isalpha(((int)key[i])))
	{	
		i++;
		while (key[i] != '\0' && ft_isalnum(key[i]))
			i++;
	}
	if (key[i] != '\0' || key[i] == ' ')
	{
		if (wall == 1)
			free_mem((void **)&key);
		return (1);
	}
	else
	{
		if (wall == 1)
			free_mem((void **)&key);
		return (0);
	}
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
