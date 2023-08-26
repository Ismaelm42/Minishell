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
