#include "../../../include/minishell.h"

/*
Fuunción para inicializar una lista
*/

t_node	*init_list(void)
{
	return (NULL);
}
/*
Función para crear un nuevo nodo en la lista.(t_node)
*/

t_node	*create_nodo(char *key, char *value)
{
	t_node	*aux;

	aux = (t_node *)malloc(sizeof(t_node));
	aux->key = key;
	aux->value = value;
	aux->next = NULL;
	return (aux);
}
/*
Función para ir añadiendo nodos a la lista en la última posición, 
tambiieen será  usado en el builds in export
*/

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
/*
Función que nos devuelve el último nodo de la lista
*/

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
/*
Función para imprimir la lista en el formato que simula export sin 
argumentos
*/

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
