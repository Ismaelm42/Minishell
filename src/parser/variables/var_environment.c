/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:47:37 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:13:31 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

char	*search_env_expand(char *var, char **env)
{
	int		len;
	int		len_str;
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=", 0);
	len = ft_strlen(str);
	while (ft_strnstr(env[i], str, len) == 0)
	{
		if (!env[i + 1])
			return (free(str), NULL);
		i++;
	}
	free(str);
	len_str = ft_strlen(env[i]);
	var = ft_substr(env[i], len, (len_str - len), 0);
	return (var);
}

int	search_env_replace(char *var, char *val, char **env, int flag)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=", 0);
	len = ft_strlen(str);
	while (ft_strnstr(env[i], str, len) == 0)
	{
		if (!env[i + 1])
		{
			free_mem((void **)&var);
			free_mem((void **)&val);
			return (free_mem((void **)&str), 1);
		}	
		i++;
	}
	free_mem((void **)&var);
	free_mem((void **)&env[i]);
	env[i] = ft_strjoin(str, val, 1);
	if (flag == 1)
		free_mem((void **)&val);
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
