#include "../../include/minishell.h"

int	buitlins(t_global *g, int n)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else
		flag = 0;
	return (flag);
}
