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

int	built_ins(t_global *g, int n, int fd_in, int fd_out)
{
	int	flag;

	flag = 1;
	fd_in = fd_in + 0;
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd(fd_in, fd_out);
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
	{
		ft_export(g, n, fd_out);
		// print_stack(g->lst_env, fd_out);
	}	
	else
		flag = 0;
	close(fd_in);
	close(fd_out);
	exit(flag);
	return (flag);
}
