#include "../../include/minishell.h"

int	check_built_ins(t_global *g, int n)
{
	//printf("comando = %s\n", g->tokens[n].command);
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0 
		|| (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "export", 7) == 0))
		return (0);
	else
		return (1);
}

int	built_ins(t_global *g, int n)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
	{
		ft_export(g, n);
		//print_stack(g->lst_env);
	}	
	else
		flag = 0;
	return (flag);
}
