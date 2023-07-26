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
	while (c != position)
		c++;
	return (ft_substr(c, 1, ft_strlen(c), 0));
}

/*
Función para crear el diccionario de variables de entorno, lista enlazada 
simulando un dicionario clave / valor
*/
void	copy_environment(t_node **lst_env, char **env)
{
	int		i;
	t_node	*aux;

	//(void)lst_env;
	i = 0;
	while (env[i] != NULL)
	{
		aux = create_nodo(extract_clue(env[i]), extract_value(env[i]));
		insert_last(lst_env, aux);
		i++;
	}
}

/*
Función para buscar una clave en un diccionario se podra usar 
tanto para el diccionario de environment como para el de variables locales,
devolvera NULL si no lo encuentra y el valor asociado si se encuentra en 
el diccionario.
*/
char	*search_key(t_node *lst, char *key)
{
	t_node	*aux;

	aux = lst;
	while (aux)
	{
		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key)) == 0)
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
		if (ft_strncmp(key, aux->key, (size_t)ft_strlen(key)) == 0)
		{
			aux->value = val;
			return (0);
		}
		else
			aux = aux->next;
	}
	return (-1);
}
