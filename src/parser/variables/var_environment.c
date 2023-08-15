#include "../../../include/minishell.h"

/*
Funcion modificada para hacer copia de environment char **env
guardando una copa excacta del tipo key = value
*/
char	**copy_environment(char **env)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[j])
	{
		env_copy[i] = ft_strdup(env[j]);
		j++;
		i++;
	}
	return (env_copy);
}

/*
funcion para liberar memoria de la copia de environments char **
*/
void	free_env(char **env_copy)
{
	int	n;

	n = 0;
	if (env_copy != NULL)
	{
		while (env_copy[n] != NULL)
		{
			free(env_copy[n]);
			env_copy[n] = NULL;
			n++;
		}
		free(env_copy);
		env_copy = NULL;
	}
}


/*
Funcion para buscar en global->env una variable de entorno key= y 
devolver su valor para la expansion del lexer 
*/

char	*search_env(char *var, char **envp)
{
	int		len;
	int		len_str;
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=", 0);
	len = ft_strlen(str);
	while (ft_strnstr(envp[i], str, len) == 0)
	{
		if (!envp[i + 1])
			return (free(str), NULL);// ft_strdup(""));
		i++;
	}
	free(str);
	len_str = ft_strlen(envp[i]);
	var = ft_substr(envp[i], len, (len_str - len),0);
	return (var);
}




