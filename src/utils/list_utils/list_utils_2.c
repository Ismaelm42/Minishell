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
		free_mem((void **)&tmp->key);
		free_mem((void **)&tmp->value);
		free_mem((void **)&tmp);
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

/*
Función para hacer copia de environments en una lista para
usarla en pricipio con comando export y unset
*/
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