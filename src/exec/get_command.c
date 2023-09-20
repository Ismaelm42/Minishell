/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:45 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/17 00:31:11 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_path(char **env);
static char	*search_path(t_global *global, int n, char **path, char *cmd_path);
static int	check_cmd_path(char *cmd, char *cmd_path, char *path, int flag);
static char	*get_command_path(t_global *global, int n);

static char	**get_path(char **env)
{
	char	**path;
	char	*path_substr;

	while (*env != NULL)
	{
		if (ft_strnstr(*env, "PATH=", 5) != NULL)
			break ;
		env++;
	}
	if (*env == NULL)
	{
		path = (char **) ft_calloc(sizeof(char *), 1);
		path[0] = NULL;
	}
	else
	{
		path_substr = ft_substr(*env, 5, ft_strlen(*env) - 5, 0);
		path = ft_split(path_substr, ':');
		free(path_substr);
	}
	return (path);
}

static char	*search_path(t_global *global, int n, char **path, char *cmd_path)
{
	int	ret;
	int	i;

	i = 0;
	if (path[i] == NULL)
	{
		access_error_message(cmd_path, ": No such file or directory\n");
		exit_child_process(global, path, cmd_path, 127);
	}
	free_mem((void **)&cmd_path);
	cmd_path = ft_strjoin(path[i], "/", 0);
	cmd_path = ft_strjoin(cmd_path, global->tokens[n].command, 1);
	while (1)
	{
		ret = check_cmd_path(global->tokens[n].command, cmd_path, path[i], 1);
		if (ret != 0 && ret != -1)
			exit_child_process(global, path, cmd_path, ret);
		else if (ret == 0)
			return (free_matrix((void ***)&path, 0), cmd_path);
		free_mem((void **)&cmd_path);
		cmd_path = ft_strjoin(path[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, global->tokens[n].command, 1);
		i++;
	}
	return (NULL);
}

static int	check_cmd_path(char *cmd, char *cmd_path, char *path, int flag)
{
	if (path == NULL && flag != 0)
	{
		access_error_message(cmd, ": command not found\n");
		return (127);
	}
	else if (access(cmd_path, F_OK) != 0)
	{
		if (flag == 0)
		{
			access_error_message(cmd_path, ": No such file or directory\n");
			return (127);
		}
		return (-1);
	}
	else if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) != 0)
	{
		access_error_message(cmd_path, ": Permission denied\n");
		if (flag == 0)
			return (126);
		return (1);
	}
	else if (access(cmd_path, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

static char	*get_command_path(t_global *global, int n)
{
	char	*cmd_path;
	char	**path;
	int		ret;

	if (global->tokens[n].command == NULL)
		return (NULL);
	path = get_path(global->env);
	cmd_path = ft_strdup(global->tokens[n].command);
	if (ft_strchr(cmd_path, '/') != NULL)
	{
		ret = check_cmd_path(NULL, cmd_path, *path, 0);
		if (ret != 0)
			exit_child_process(global, path, cmd_path, ret);
		else
			return (free_matrix((void ***)&path, 0), cmd_path);
	}
	return (search_path(global, n, path, cmd_path));
}

char	**get_exec_command(t_global *global, int n)
{
	char	**cmd_exec;
	char	*cmd_path;
	int		length;
	int		i;

	cmd_path = get_command_path(global, n);
	if (cmd_path == NULL)
		exit_child_process(global, NULL, NULL, 0);
	length = 0;
	while (global->tokens[n].arg[length] != NULL)
		length++;
	length++;
	cmd_exec = (char **)ft_calloc(sizeof(char *), length + 1);
	cmd_exec[0] = ft_strdup(cmd_path);
	i = 0;
	while ((i + 1) < length)
	{
		cmd_exec[i + 1] = ft_strdup(global->tokens[n].arg[i]);
		i++;
	}
	cmd_exec[i + 1] = NULL;
	free_mem((void **)&cmd_path);
	return (cmd_exec);
}
