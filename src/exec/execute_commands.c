#include "../../include/minishell.h"

int	create_pipes_and_pid(t_global *global)
{
	int	n;

	n = 0;
	global->fd = (int **)ft_calloc(sizeof(int *), global->pipeline + 1);
	while (n < global->pipeline + 1)
	{
		global->fd[n] = (int *)ft_calloc(sizeof(int), 2);
		if (pipe(global->fd[n]) == -1)
			return (print_error("Pipeline error", errno), 1);
		n++;
	}
	global->pid = (pid_t *)ft_calloc(sizeof(pid_t), global->pipeline);
	if (global->pid == NULL)
		return (1);
	return (0);
}

int	child_process(t_global *global, int n)
{
	char	**command_line;

	fd_closer(global->fd, global->pipeline, n);
	if (check_builtins(global, n) != 0)
		command_line = get_exec_command(global, n);
	if (fd_in_handler(global, n) != 0)
		return (1);
	if (fd_out_handler(global, n) != 0)
		return (1);
	if (check_builtins(global, n) == 0)
		builtins(global, n);
	if (command_line == NULL)
	{
		free_global(global, 1);
		exit(1);
	}
	execve(command_line[0], command_line, global->env);
	print_error(command_line[0], errno);
	return (free_matrix((void ***)&command_line, 0), errno);
}

int	parent_process(t_global *global, int n)
{
	int		i;
	int		status;

	i = 0;
	fd_closer(global->fd, global->pipeline, n);
	while (i < global->pipeline)
		waitpid(global->pid[i++], &status, 0);
	if (dup2(global->fd[n][0], STDIN_FILENO) == -1)
		return (print_error("Pipeline error", errno), 1);
	write_on_fd(global->fd[n][0], STDOUT_FILENO);
	close(global->fd[n][0]);
	if (dup2(global->fd_stdin, STDIN_FILENO) == -1)
		return (print_error("Pipeline error", errno), 1);
	if (dup2(global->fd_stdout, STDOUT_FILENO) == -1)
		return (print_error("Pipeline error", errno), 1);
	return (0);
}

int	execute_commands(t_global *global)
{
	int		n;

	if (check_edge_builtins(global) == 1 || process_heredocs(global) == 1
		|| create_pipes_and_pid(global) == 1)
		return (1);
	n = 0;
	while (n < global->pipeline)
	{
		global->pid[n] = fork();
		if (global->pid[n] == -1)
			return (print_error("Fork error", errno), 1);
		if (global->pid[n] == 0)
			if (child_process(global, n) != 0)
				return (1);
		n++;
	}
	if (parent_process(global, n) != 0)
		return (1);
	return (0);
}
