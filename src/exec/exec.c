#include "../../include/minishell.h"

int	child_process(t_global *global, char **cmd, int *fd)
{
	close(fd[0]);
	global->exit_status = dup2(fd[1], STDOUT_FILENO);
	if (global->exit_status == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		strerror(-1);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(fd[1]);
	global->exit_status = execve(cmd[0], cmd, global->env);
	if (global->exit_status == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		strerror(-1);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

int	parent_process(t_global *global, int *fd)
{
	char	*str;
	char	*str2;

	close(fd[1]);
	close(STDIN_FILENO);
	while (str != NULL)
		printf("str1 = %s\n", str = gnl(fd[0]));
	global->exit_status = dup2(STDOUT_FILENO, fd[0]);
	close(STDOUT_FILENO);
	while (str2 != NULL)
		printf("str2 = %s\n", str2 = gnl(STDOUT_FILENO));
	if (global->exit_status == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		strerror(-1);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	exec(t_global *global)
{
	char	**command;
	int		fd[2];
	pid_t	pid;
	int		n;

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("minishell: error creating pipe\n", 2);
		return (1);
	}
	n = 0;
	// while (n < global->pipeline)
	// {
		command = get_exec_command(global, n);
		printf("cmd = %s\n", command[0]);
		pid = fork();
		if (pid == 0)
			child_process(global, command, fd);
		else
			parent_process(global, fd);
	// 	n++;
	// }
	return (0);
}
