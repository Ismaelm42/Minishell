/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:33:24 by javier            #+#    #+#             */
/*   Updated: 2023/09/21 12:13:25 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		pid_child_process(t_global *pid_global, int n);
static char		*pid_parent_process(t_global *pid_global, int n);

static void	pid_child_process(t_global *pid_global, int n)
{
	char	**pid_command;

	fd_closer(pid_global->fd, pid_global->pipeline, n);
	pid_command = get_exec_command(pid_global, n);
	if (dup2(pid_global->fd[n][0], STDIN_FILENO) == -1
		|| dup2(pid_global->fd[n + 1][1], STDOUT_FILENO) == -1)
	{
		free_global(pid_global, 1);
		exit(-1);
	}
	close(pid_global->fd[n][0]);
	close(pid_global->fd[n + 1][1]);
	execve(pid_command[0], pid_command, pid_global->env);
	free_matrix((void ***)&pid_command, 0);
	free_global(pid_global, 1);
	exit(-1);
}

static char	*pid_parent_process(t_global *pid_global, int n)
{
	char	*pid;
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
	pid = (char *)ft_calloc(sizeof(char), 5 + 1);
	if (read(pid_global->fd[n][0], pid, 5) == -1)
		return (free_mem((void **)&pid), free_global(pid_global, 1), NULL);
	close(pid_global->fd[n][0]);
	tcsetattr(STDIN_FILENO, TCSANOW, &pid_global->prompt);
	free_global(pid_global, 1);
	return (pid);
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
