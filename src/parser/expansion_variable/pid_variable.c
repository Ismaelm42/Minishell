#include "../../../include/minishell.h"

void	pid_child_process(t_global *pid_global, int n)
{
	char	**command_line;

	fd_closer(pid_global->fd, pid_global->pipeline, n);
	command_line = get_exec_command(pid_global, n);
	if (dup2(pid_global->fd[n][0], STDIN_FILENO) == -1
		|| dup2(pid_global->fd[n + 1][1], STDOUT_FILENO) == -1)
	{
		free_global(pid_global, 1);
		exit(-1);
	}
	close(pid_global->fd[n][0]);
	close(pid_global->fd[n + 1][1]);
	execve(command_line[0], command_line, pid_global->env);
	free_matrix((void ***)&command_line, 0);
	free_global(pid_global, 1);
	exit(-1);
}

char	*pid_parent_process(t_global *pid_global, int n)
{
	char	*buffer;
	int		exit_status;
	int		i;

	i = 0;
	fd_closer(pid_global->fd, pid_global->pipeline, n);
	while (i < pid_global->pipeline)
	{
		waitpid(pid_global->pid[i++], &exit_status, 0);
		if (exit_status == -1)
			return (free_global(pid_global, 1), NULL);
	}
	buffer = (char *)ft_calloc(sizeof(char), (5 + 1));
	if (read(pid_global->fd[n][0], buffer, (5 + 1)) == -1)
	{
		free_mem((void **)&buffer);
		free_global(pid_global, 1);
		return (NULL);
	}
	close(pid_global->fd[n][0]);
	tcsetattr(STDIN_FILENO, TCSANOW, &pid_global->prompt);
	free_global(pid_global, 1);
	return (buffer);
}

char	*get_pid_process(t_global *global)
{
	t_global	*pid_global;
	char		*pid_input;
	int			n;

	pid_global = init_struct(global->env);
	pid_input = ft_strdup("ps -o ppid= | tail -n 1\
	| sed 's/^[[:space:]]*//' | tr -d '\n'");
	get_struct_data(pid_global, pid_input);
	create_pipes_and_pid(pid_global);
	n = 0;
	while (n < pid_global->pipeline)
	{
		pid_global->pid[n] = fork();
		if (pid_global->pid[n] == -1)
			return (free_global(pid_global, 1), NULL);
		if (pid_global->pid[n] == 0)
			pid_child_process(pid_global, n);
		n++;
	}
	return (pid_parent_process(pid_global, n));
}
