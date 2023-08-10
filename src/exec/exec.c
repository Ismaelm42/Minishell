#include "../../include/minishell.h"

int	create_pipes_and_pid(t_global *global, pid_t **pid, int ***fd)
{
	int	n;

	n = 0;
	*fd = (int **)ft_calloc(sizeof(int *), global->pipeline + 1);
	while (n < global->pipeline + 1)
	{
		(*fd)[n] = (int *)ft_calloc(sizeof(int), 2);
		if (pipe((*fd)[n]) == -1)
			return (ft_putstr_fd("minishell: error creating pipe\n", 2), 1);
		n++;
	}
	*pid = (int *)ft_calloc(sizeof(int), global->pipeline);
	if (*pid == NULL)
		return (1);
	return (0);
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

int	child_process(t_global *global, int **fd, int n)
{
	char	**command_line;

	command_line = get_exec_command(global, n);
	fd_closer(fd, global->pipeline, n);
	if (dup2(fd[n][0], STDIN_FILENO) == -1)
		return (ft_putstr_fd("minishell: error redirecting pipe\n", 2), 1);
	close(fd[n][0]);
	if (dup2(fd[n + 1][1], STDOUT_FILENO) == -1)
		return (ft_putstr_fd("minishell: error redirecting pipe\n", 2), 1);
	close(fd[n + 1][1]);
	execve(command_line[0], command_line, global->env);
	print_execve_error(command_line[0], errno);
	return (errno);
}

int	parent_process(t_global *global, int **fd, int n)
{
	char	*buffer;

	fd_closer(fd, global->pipeline, n);
	if (dup2(fd[n][0], STDIN_FILENO) == -1)
		return (ft_putstr_fd("minishell: error redirecting pipe\n", 2), 1);
	while (1)
	{
		buffer = gnl(fd[n][0]);
		if (buffer == NULL)
			break ;
		write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(fd[n][0]);
	return (0);
}

int	exec(t_global *global)
{
	int		**fd;
	pid_t	*pid;
	int		n;

	if (create_pipes_and_pid(global, &pid, &fd) == 1)
		return (1);
	n = 0;
	while (n < global->pipeline)
	{
		pid[n] = fork();
		if (pid[n] == -1)
			return (ft_putstr_fd("minishell: error creating fork\n", 2), 1);
		if (pid[n] == 0)
			if (child_process(global, fd, n) != 0)
				return (1);
		n++;
	}
	if (parent_process(global, fd, n) != 0)
		return (1);
	return (0);
}
