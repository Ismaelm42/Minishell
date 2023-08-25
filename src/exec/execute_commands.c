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
			return (print_error("Pipeline error", errno), 1);
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

	if (check_built_ins(global, n) == 1)
		command_line = get_exec_command(global, n);
	fd_closer(fd, global->pipeline, n);
	if (fd_in_handler(global, n, fd[n][0], fd[n + 1][1]) != 0)
		return (1);
	if (fd_out_handler(global, n, fd[n + 1][1]) != 0)
		return (1);
	if (check_built_ins(global, n) == 0)
		built_ins(global, n, fd[n][0], fd[n + 1][1]);
	else
	{
		close(fd[n][0]);
		close(fd[n + 1][1]);
		execve(command_line[0], command_line, global->env);
		print_error(command_line[0], errno);
	}
	return (errno);
}

int	parent_process(t_global *global, int **fd, pid_t *pid, int n)
{
	int		status;

	n = 0;
	while (n < global->pipeline)
		waitpid(pid[n++], &status, WNOHANG);
	fd_closer(fd, global->pipeline, n);
	if (dup2(fd[n][0], STDIN_FILENO) == -1)
		return (print_error("Pipeline error1", errno), 1);
	write_on_fd(fd[n][0], STDOUT_FILENO);
	close(fd[n][0]);
	if (dup2(global->fd_stdin, STDIN_FILENO) == -1)
		return (print_error("Pipeline error2", errno), 1);
	if (dup2(global->fd_stdout, STDOUT_FILENO) == -1)
		return (print_error("Pipeline error3", errno), 1);
	return (0);
}

int	execute_commands(t_global *global)
{
	pid_t	*pid;
	int		**fd;
	int		n;

	//meter *pid y **fd en el global

	// export ARG=PEPE | echo hola
	// Si aparece este comando en los built_ins se hace exit sin hacer nada
	//No tiene que hacer nada

	// export | cat -e
	// Si aparece este comando, tienes que escribir en el fd correspondiente la lista de export

	// export ARG=PEPE
	// Si global->pipeline es == 1, se realiza el export y se hace return para que no entre ni cree pipes/procesos hijos
	//n = 0;
	if (global->tokens == NULL)
		return (1);
	if (ft_strncmp(global->tokens[0].command, "export", 7) == 0)
	{
		if (global->tokens[0].arg[0] != NULL)
		{
			action_export(global, 0, 0);
			return (0);
		}
	}
	if (process_heredocs(global) == 1)
		return (1);
	if (create_pipes_and_pid(global, &pid, &fd) == 1)
		return (1);
	n = 0;
	while (n < global->pipeline)
	{
		pid[n] = fork();
		if (pid[n] == -1)
			return (print_error("Fork error", errno), 1);
		if (pid[n] == 0)
			if (child_process(global, fd, n) != 0)
				return (1);
		n++;
	}
	if (parent_process(global, fd, pid, n) != 0)
		return (1);
	return (0);
}
