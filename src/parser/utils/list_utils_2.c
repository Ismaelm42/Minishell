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
