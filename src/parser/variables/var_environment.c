#include "../../../include/minishell.h"

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

/*
Funcion modificada para hacer copia de environment char **env
guardando una copa excacta.
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
// void	free_env(char **env_copy)
// {
// 	int	n;

// 	n = 0;
// 	if (env_copy != NULL)
// 	{
// 		while (env_copy[n] != NULL)
// 		{
// 			free(env_copy[n]);
// 			env_copy[n] = NULL;
// 			n++;
// 		}
// 		free(env_copy);
// 		env_copy = NULL;
// 	}
// }


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
	var = ft_substr(envp[i], len, (len_str - len), 0);
	return (var);
}

int	search_env_replace(char *var, char *val, char **envp)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=", 0);
	len = ft_strlen(str);
	while (ft_strnstr(envp[i], str, len) == 0)
	{
		if (!envp[i + 1])
		{
			free(var);
			free(val);
			return (free(str), 1);
		}	
		i++;
	}
	free(envp[i]);
	envp[i] = ft_strjoin(str, val, 3);
	return (0);
}
void	add_env(char ***env, char *argv)
{
	char	**env_cp;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i + 2));
	i = -1;
	while ((*env)[++i])
			env_cp[i] = ft_strdup((*env)[i]);
	env_cp[i] = ft_strdup(argv);
	free_matrix((void ***)env, 0);
	*env = env_cp;
}
