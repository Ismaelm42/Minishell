#include "../../include/minishell.h"

int	buitlins(t_global *g, int n)
{
	int	flag;

	flag = 1;
	//printf("entra en el menu de builtin\n");
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
		ft_export(g, n);
	else
		flag = 0;
	return (flag);
}