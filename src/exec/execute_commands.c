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

//se cierran los fd en fd_in_handler (si hay algún problema se cierra tanto el de 
//lectura como el de escritura) y en fd_out_handler (solo el de escritura ya que
//el otro está cerrado)
//se ha suprimido el else delante del execve ya que no es necesario puesto que si
//es un building se sale del child_process con un exit y termina el programa
//en ese proceso hijo.

int	child_process(t_global *global, int n)
{
	char	**command_line;

	if (check_builtins(global, n) == 1)
		command_line = get_exec_command(global, n);
	fd_closer(global->fd, global->pipeline, n);
	if (fd_in_handler(global, n) != 0)
		return (1);
	if (fd_out_handler(global, n) != 0)
		return (1);
	if (check_builtins(global, n) == 0)
		builtins(global, n);
	execve(command_line[0], command_line, global->env);
	print_error(command_line[0], errno);
	return (errno);
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

	// export ARG=PEPE | echo hola
	// Si aparece este comando en los builtins se hace exit sin hacer nada
	//No tiene que hacer nada

	// export | cat -e
	// Si aparece este comando, tienes que escribir en el fd correspondiente la lista de export

	// export ARG=PEPE
	// Si global->pipeline es == 1, se realiza el export y se hace return para que no entre ni cree pipes/procesos hijos
	if (global->tokens == NULL)
		return (1);

	//dprintf(1, "global ->pipeline = %d \n", global->pipeline);
	if (ft_strncmp(global->tokens[0].command, "export", 7) == 0 && global->pipeline == 1)
	{
		if (global->tokens[0].arg[0] != NULL)
		{
			action_export(global, 0, 0);
			return (0);
		}
	}
	if (ft_strncmp(global->tokens[0].command, "unset", 6) == 0 && global->pipeline == 1)
	{
		if (global->tokens[0].arg[0] != NULL)
		{
			ft_unset(global, 0);
			return (0);
		}
	}
	if (ft_strncmp(global->tokens[0].command, "cd", 3) == 0 && global->pipeline == 1)
	{
		ft_cd(global, 0);
		return (0);
	}
	if (process_heredocs(global) == 1)
		return (1);
	if (create_pipes_and_pid(global) == 1)
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
