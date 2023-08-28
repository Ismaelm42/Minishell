#include "../../include/minishell.h"

void	ft_echo(t_global *g, int n)
{
	int	i;

    i = -1;
	if (ft_strncmp(g->tokens[n].arg[0], "-n", 3) == 0)
		i++;
	while (g->tokens[n].arg[++i])
	{	
		ft_putstr_fd(g->tokens[n].arg[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (ft_strncmp(g->tokens[n].arg[0], "-n", 3) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
