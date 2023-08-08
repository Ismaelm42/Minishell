#include "../../include/minishell.h"

char	**get_path(char **env)
{
	char	**path;
	char	*path_substr;

	while (*env != NULL)
	{
		if (ft_strnstr(*env, "PATH=", 5) != NULL)
			break ;
		env++;
	}
	path_substr = ft_substr(*env, 5, ft_strlen(*env) - 5, 0);
	path = ft_split(path_substr, ':');
	free(path_substr);
	return (path);
}

int	check_cmd_path(char *cmd, char *cmd_path, char *path, int flag)
{
	if (path == NULL)
	{
		access_error_message(cmd, ": command not found\n");
		return (-1);
	}
	else if (access(cmd_path, F_OK) != 0)
	{
		if (flag == 0)
			access_error_message(cmd_path, ": no such file or directory\n");
		return (1);
	}
	else if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) != 0)
	{
		access_error_message(cmd_path, ": permission denied\n");
		return (-2);
	}
	else if (access(cmd_path, F_OK | X_OK) == 0)
		return (0);
	return (1);
}

char	*get_command_path(t_global *global, int n)
{
	char	*cmd_path;
	char	**path;

	path = get_path(global->env);
	cmd_path = ft_strdup(global->tokens[n].command);
	if (ft_strchr(cmd_path, '/') != NULL)
	{
		if (check_cmd_path(NULL, cmd_path, *path, 0) != 0)
		{
			free(cmd_path);
			free_matrix(path);
			return (NULL);
		}
		else
		{
			free_matrix(path);
			return (cmd_path);
		}
	}
	return (search_in_path(global, n, path, cmd_path));
}

char	**get_exec_command(t_global *global, int n)
{
	char	**cmd_exec;
	char	*cmd_path;
	int		length;
	int		i;

	cmd_path = get_command_path(global, n);
	if (cmd_path == NULL)
		return (NULL);
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
	free(cmd_path);
	return (cmd_exec);
}
