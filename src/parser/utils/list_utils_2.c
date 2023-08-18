#include "../../../include/minishell.h"

/*
Función para liberar una lista (nuestros diccionarios) al cerrar el  programa.
*/
void	ft_free_lst(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
/*
Función para calcular numero de nodos d euna lista no se usa aún.
*/

int	ft_size_lst(t_node *lst)
{
	int		count;
	t_node	*aux;

	aux = lst;
	count = 0;
	while (aux)
	{
		aux = aux->next;
		count++;
	}
	return (count);
}

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

/*
Funcion que ordena la lista de environment alfabaticamente
*/
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