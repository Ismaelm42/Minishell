#include "../../include/minishell.h"

int	check_builtins(t_global *g, int n)
{
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0 
		|| (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "export", 7) == 0))
		return (0);
	else
		return (1);
}

int	builtins(t_global *g, int n)
{
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
		ft_export(g, n);
	free_global(g, 1);
	exit(1);
}
