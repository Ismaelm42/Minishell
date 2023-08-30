#include "../../include/minishell.h"

int	check_edge_builtins(t_global *global)
{
	if (global->tokens[0].command == NULL)
		return (0);
	if (ft_strncmp(global->tokens[0].command, "export", 7) == 0 && global->pipeline == 1)
		if (global->tokens[0].arg[0] != NULL)
			return (action_export(global, 0, 0), 1);
	if (ft_strncmp(global->tokens[0].command, "unset", 6) == 0 && global->pipeline == 1)
		if (global->tokens[0].arg[0] != NULL)
			return (ft_unset(global, 0), 1);
	if (ft_strncmp(global->tokens[0].command, "cd", 3) == 0 && global->pipeline == 1)
		return (ft_cd(global, 0), 1);
	return (0);
}

int	check_builtins(t_global *g, int n)
{
	if (g->tokens[n].command == NULL
		|| (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
		|| (ft_strncmp(g->tokens[n].command, "unset", 6) == 0)
		|| (ft_strncmp(g->tokens[n].command, "echo", 5) == 0)
		|| (ft_strncmp(g->tokens[n].command, "cd", 3) == 0))
		return (0);
	else
		return (1);
}

void	builtins(t_global *g, int n)
{
	if (g->tokens[n].command != NULL)
	{
		if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
			ft_pwd(1);
		else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
			ft_env(g);
		else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
			ft_export(g, n);
		else if (ft_strncmp(g->tokens[n].command, "unset", 6) == 0)
			ft_unset(g, n);
		else if (ft_strncmp(g->tokens[n].command, "echo", 5) == 0)
			ft_echo(g, n);
		else if (ft_strncmp(g->tokens[n].command, "cd", 3) == 0)
			ft_cd(g, n);
	}
	free_global(g, 1);
	exit(1);
}
	