#include "../../include/minishell.h"

void	access_error_message(char *error, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(message, 2);
}

char	*search_in_path(t_global *global, int n, char **path, char *cmd_path)
{
	int	ret;
	int	i;

	i = 0;
	while (1)
	{
		ret = check_cmd_path(global->tokens[n].command, cmd_path, path[i], 1);
		if (ret == -1 || ret == -2)
		{
			free(cmd_path);
			free_matrix(path);
			return (NULL);
		}
		else if (ret == 0)
		{
			free_matrix(path);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = ft_strjoin(path[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, global->tokens[n].command, 1);
		i++;
	}
	return (NULL);
}

void	fd_closer(int **fd, int pipeline, int n)
{
	int		i;

	i = 0;
	while (i < pipeline + 1)
	{
		if (i != n)
			close(fd[i][0]);
		if (i != n + 1)
			close(fd[i][1]);
		i++;
	}
}

void	print_execve_error(char *command, int code_error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	strerror(code_error);
	ft_putstr_fd("\n", 2);
}
