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
		access_error_message(cmd, ": Command not found\n");
		return (-1);
	}
	else if (access(cmd_path, F_OK) != 0)
	{
		if (flag == 0)
			access_error_message(cmd_path, ": No such file or directory\n");
		return (1);
	}
	else if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) != 0)
	{
		access_error_message(cmd_path, ": Permission denied\n");
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

	if (global->tokens[n].command == NULL)
		return (NULL);
	path = get_path(global->env);
	cmd_path = ft_strdup(global->tokens[n].command);
	if (ft_strchr(cmd_path, '/') != NULL)
	{
		if (check_cmd_path(NULL, cmd_path, *path, 0) != 0)
			return (free(cmd_path), free_matrix((void ***)&path, 0), NULL);
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
		return (NULL);
	//AQUI ESTO OCURRE CUANDO NO HAY COMANDO. HAY QUE VER CÓMO TRATARLO PARA EXIT_STATUS
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
