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
		{
			global->exit_status = -1;
			return (print_error("Pipeline error", errno), 1);
		}
		n++;
	}
	global->pid = (pid_t *)ft_calloc(sizeof(pid_t), global->pipeline);
	return (0);
}

void	child_process(t_global *global, int n)
{
	char	**command_line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	fd_closer(global->fd, global->pipeline, n);
	handle_files(global, n);
	command_line = check_builtins(global, n);
	execve(command_line[0], command_line, global->env);
	free_matrix((void ***)&command_line, 0);
	print_error(command_line[0], errno);
	exit(errno);
}

int	parent_process(t_global *global, int n)
{
	int	i;

	i = 0;
	fd_closer(global->fd, global->pipeline, n);
	close(global->fd[n][0]);
	while (i < global->pipeline)
	{
		waitpid(global->pid[i++], &global->exit_status, 0);
		if (WIFEXITED(global->exit_status))
			global->exit_status = WEXITSTATUS(global->exit_status);
		if (global->exit_status == 139)
			global->exit_status = 126;
	}
	if (dup2(global->fd_stdin, STDIN_FILENO) == -1)
		return (print_error("Pipeline error", errno), -1);
	if (dup2(global->fd_stdout, STDOUT_FILENO) == -1)
		return (print_error("Pipeline error", errno), -1);
	return (0);
}

void	handler_prueba(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	execute_commands(t_global *global)
{
	int	n;

	if (check_edge_builtins(global) == 1 || process_heredocs(global) == 1
		|| create_pipes_and_pid(global) == 1)
		return (1);
	n = 0;
	while (n < global->pipeline)
	{
		signal(SIGINT, ft_sigint_proc);
		signal(SIGQUIT, ft_sigint_proc);
		global->pid[n] = fork();
		if (global->pid[n] == -1)
		{
			global->exit_status = -1;
			return (print_error("Fork error", errno), 1);
		}
		if (global->pid[n] == 0)
			child_process(global, n);
		n++;
	}
	return (parent_process(global, n));
}
