#include "../../../include/minishell.h"

/*
Función para extraer del string enviroments la clave 
*/
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
/*
Función para extraer del string environments el valor de la variable de entorno
*/

char	*extract_value(char *c)
{
	char	*position;

	position = ft_strchr(c, 61);
	while (c != position && c != NULL)
		c++;
	return (ft_substr(c, 1, ft_strlen(c), 0));
}

/*
Función para buscar una clave en diccionario (lista) de variables locales,
devolvera NULL si no lo encuentra y el valor asociado si se encuentra en 
el diccionario.
*/
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

/*
Funcion para machacar el valor en el diccionario de variables
locales si recibimos por input una nueva asignacion $ARG=pepito
y mas tarde $ARG=Juan x ejemplo.
*/

int	search_key_and_replace(t_node *lst, char *key, char *val)
{
	t_node	*aux;

	aux = lst;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key) + 1) == 0)
		{
			free_mem((void **)&key);
			free_mem((void **)&aux->value);
			aux->value = val;
			return (0);
		}
		else
			aux = aux->next;
	}
	free_mem((void **)&key);
	free_mem((void **)&val);
	return (-1);
}

//Funcion que una vez comprobada la entrada primero busca si la variable 
//ya esta metida en el diccionario, en tal caso reemplaza su valor y si 
//no  esta la añade

void	put_dictionary_local(char *nv, t_global *g)
{
	char	*key;
	t_node	*aux;

	key = extract_clue(g->input);
	if (search_key_and_replace(g->lst_local, key, nv) != 0)
	{
		aux = create_nodo(key, nv);
		insert_last(&(g)->lst_local, aux);
	}
	else
		free_mem((void **)&key);
}
