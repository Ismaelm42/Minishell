#include "../../include/minishell.h"

void	access_error_message(char *error, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(message, 2);
}

char	*search_path(t_global *global, int n, char **path, char *cmd_path)
{
	int	ret;
	int	i;

	i = 0;
	free_mem((void **)&cmd_path);
	cmd_path = ft_strjoin(path[i], "/", 0);
	cmd_path = ft_strjoin(cmd_path, global->tokens[n].command, 1);
	while (1)
	{
		ret = check_cmd_path(global->tokens[n].command, cmd_path, path[i], 1);
		if (ret == -1 || ret == -2)
		{
			free_mem((void **)&cmd_path);
			free_matrix((void ***)&path, 0);
			return (NULL);
		}
		else if (ret == 0)
			return (free_matrix((void ***)&path, 0), cmd_path);
		free_mem((void **)&cmd_path);
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

void	print_error(char *message, int code_error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(code_error), 2);
	ft_putstr_fd("\n", 2);
}

void	write_on_fd(int fd_in, int fd_out)
{
	char	*buffer;

	while (1)
	{
		buffer = gnl(fd_in);
		if (buffer == NULL)
			break ;
		ft_putstr_fd(buffer, fd_out);
		free_mem((void **)&buffer);
	}
}
