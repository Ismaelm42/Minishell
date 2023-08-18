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
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), global->pipeline);
	if (*pid == NULL)
		return (1);
	return (0);
}

int	child_process(t_global *global, int **fd, int n)
{
	char	**command_line;

	command_line = get_exec_command(global, n);
	fd_closer(fd, global->pipeline, n);
	if (fd_in_handler(global, n, fd[n][0], fd[n + 1][1]) != 0)
		return (1);
	if (fd_out_handler(global, n, fd[n + 1][1]) != 0)
		return (1);
	if (command_line == NULL)
		return (1);
	else
		execve(command_line[0], command_line, global->env);
	print_execve_error(command_line[0], errno);
	return (errno);
}

int	parent_process(t_global *global, int **fd, int n)
{
	fd_closer(fd, global->pipeline, n);
	if (dup2(fd[n][0], STDIN_FILENO) == -1)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	write_on_fd(fd[n][0], STDOUT_FILENO);
	close(fd[n][0]);
	return (0);
}

int	execute_commands(t_global *global)
{
	int		status;
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
	n = 0;
	printf("global->pipeline = %d\n", global->pipeline);
	while (n < global->pipeline)
	{
		printf("n = %d\n", n);
		waitpid(pid[n++], &status, 0);
	}
	printf("paso a proceso padre\n");
	if (parent_process(global, fd, n) != 0)
		return (1);
	return (0);
}
