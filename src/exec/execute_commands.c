/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:31 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/17 00:30:40 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		child_process(t_global *global, int n);
static int		parent_process(t_global *global, int n);
static void		update_environment_(t_global *g);

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

static void	child_process(t_global *global, int n)
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
	exit(1);
}

static int	parent_process(t_global *global, int n)
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
		if (global->exit_status == 11)
			global->exit_status = 126;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &global->prompt);
	return (0);
}

static void	update_environment_(t_global *g)
{
	int	i;

	i = 0;
	if (g->pipeline == 1)
	{
		if (search_env("_", g->env) == 1)
		{
			add_env(&g->env, "_=");
			insert_last(&g->lst_env, create_nodo(ft_strdup("_"), strdup("")));
		}
		if (g->tokens->arg[0] == NULL)
		{
			search_key_and_replace(g->lst_env, "_", \
			ft_strdup(g->tokens->command), 0);
			search_env_replace(ft_strdup("_"), g->tokens->command, g->env, 0);
		}
		else
		{
			while (g->tokens->arg[i] != NULL)
				i++;
			search_key_and_replace(g->lst_env, "_", \
			ft_strdup(g->tokens->arg[--i]), 0);
			search_env_replace(ft_strdup("_"), g->tokens->arg[i], g->env, 0);
		}
	}
}

int	execute_commands(t_global *global)
{
	int	n;

	if (check_edge_builtins(global) == 1 || process_heredocs(global) == 1
		|| create_pipes_and_pid(global) == 1)
		return (1);
	n = 0;
	update_environment_(global);
	while (n < global->pipeline)
	{
		signal(SIGINT, ft_sig_proc);
		signal(SIGQUIT, ft_sig_proc);
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
