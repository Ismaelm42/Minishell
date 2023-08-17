#include "../../../include/minishell.h"

//Función que chequea sintacticamente la clave (ARG) 

int	check_key(char *key)
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
		free(key);
		key = NULL;
		return (1);
	}
	else
	{
		free(key);
		key = NULL;
		return (0);
	}
}