#include "../../../include/minishell.h"

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
Funcion para buscar en global->env una variable de entorno key= y 
devolver su valor para la expansion del lexer 
*/

char	*search_env_expand(char *var, char **envp)
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
			return (free(str), NULL);
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
			free_mem((void **)&var);
			free_mem((void **)&val);
			return (free_mem((void **)&str), 1);
		}	
		i++;
	}
	free_mem((void **)&var);
	free_mem((void **)&envp[i]);
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

int	search_env(char *var, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=", 0);
	while (ft_strnstr(env[i], str, ft_strlen(str)) == 0)
	{
		if (!env[i + 1])
			return (free(str), 1);
		i++;
	}
	free(str);
	return (0);
}
void delete_var_env(char ***env, char *key)
{
	char	**env_cp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (search_env(key, *env) == 0)
	{
		while ((*env)[i])
			i++;
		env_cp = ft_calloc(sizeof(char *), i + 1);
		i = 0;
		while ((*env)[i])
		{
			if (ft_strncmp(key, (*env)[i], ft_strlen(key)))
			{
				env_cp[j] = ft_strdup((*env)[i]);
				j++;
			}
			i++;
		}
		free_matrix((void ***)env, 0);
		*env = env_cp;
	}
}
