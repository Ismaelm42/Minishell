#include "../../include/minishell.h"

int	check_builtins(t_global *g, int n)
{
	//printf("comando = %s\n", g->tokens[n].command);
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0 
		|| (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "export", 7) == 0))
		return (0);
	else
		return (1);
}

int	builtins(t_global *g, int n)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd(g->fd[n][0], g->fd[n + 1][1]);
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g, g->fd[n + 1][1]);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
	{
		ft_export(g, n, g->fd[n + 1][1]);
		// print_stack(g->lst_env, fd_out);
	}	
	else
		flag = 0;
	close(g->fd[n][0]);
	close(g->fd[n + 1][1]);
	free_global(g, 1);
	exit(flag);
	return (flag);
}
