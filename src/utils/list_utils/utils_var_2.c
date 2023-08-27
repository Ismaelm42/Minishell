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
	if (key[i] != '\0')
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

int	 search_key_and_delete(t_node **lst, char *key)
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
		return (1); // NO lo ha encontrado
	else
	{
		if (aux == *lst)
			*lst = aux ->next;
		else
			aux_prev->next = aux->next;
		aux->next = NULL;
		ft_free_lst(aux); //LIBERARIA HASTA NULL?¿?¿
	}
	//print_stack(*lst);
	return (0);
}
// int	search_key_and_replace(t_node *lst, char *key, char *val)
// {
// 	t_node	*aux;

// 	aux = lst;
// 	while (aux)
// 	{
// 		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key) + 1) == 0)
// 		{
// 			free_mem((void **)&key);
// 			free_mem((void **)&aux->value);
// 			aux->value = val;
// 			return (0);
// 		}
// 		else
// 			aux = aux->next;
// 	}
// 	free_mem((void **)&key);
// 	free_mem((void **)&val);
// 	return (-1);
// }