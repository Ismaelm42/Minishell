#include "../../include/minishell.h"

int	**pipe_generator(int pipeline)
{
	int	**fd;
	int	n;

	fd = (int **)ft_calloc(sizeof(int *), pipeline);
	n = 0;
	while (n < pipeline)
	{
		fd[n] = (int *)ft_calloc(sizeof(int), 2);
		n++;
	}
	n = 0;
	while (n < pipeline)
	{
		if (pipe(fd[n]) == -1)
		{
			ft_putstr_fd("minishell: error creating pipe\n", 2);
			return (NULL);
		}
		n++;
	}
	return (fd);
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

void	child_process(t_global *global, int **fd, int n)
{
	char	**command_line;
	// char	*buffer;

	command_line = get_exec_command(global, n);
	fd_closer(fd, global->pipeline, n);
	dup2(fd[n][0], STDIN_FILENO);
	close(fd[n][0]);
	// buffer = gnl(fd[n][0]);
	// while (buffer != NULL)
	// {
	// 	dprintf(2, "buffer fd[%d][0] = %s", n, buffer);
	// 	free(buffer);
	// 	buffer = gnl(fd[n][0]);
	// }
	dup2(fd[n + 1][1], STDOUT_FILENO);
	close(fd[n + 1][1]);
	execve(command_line[0], command_line, global->env);
}

void	parent_process(t_global *global, int **fd, int n)
{
	char	*buffer;

	fd_closer(fd, global->pipeline, n);
	dup2(fd[n][0], STDIN_FILENO);
	buffer = gnl(fd[n][0]);
	while (buffer != NULL)
	{
		dprintf(2, "parent buffer fd[%d][0] = %s", n, buffer);
		free(buffer);
		buffer = gnl(fd[n][0]);
	}
	close(fd[n][0]);
	close(fd[n + 1][1]);
}

int	exec(t_global *global)
{
	int		**fd;
	pid_t	*pid;
	int		n;

	printf("pipeline = %d\n\n\n", global->pipeline);
	fd = pipe_generator(global->pipeline + 1);
	if (fd == NULL)
		return (1);
	pid = (int *)ft_calloc(sizeof(int), global->pipeline);
	n = 0;
	while (n < global->pipeline)
	{
		pid[n] = fork();
		if (pid[n] == -1)
		{
			ft_putstr_fd("minishell: error creating fork process\n", 2);
			return (1);
		}
		if (pid[n] == 0)
			child_process(global, fd, n);
		n++;
	}
	parent_process(global, fd, n);
	return (0);
}
