#include "../../include/minishell.h"

void	ft_exit(t_global *g, int n)
{
	int	i;

	i = 0;
	if (g->tokens[n].arg[0] != NULL && g->tokens[n].arg[1] != NULL)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		exit (1);
	}	

	else if (g->tokens[n].arg[0])
	{
		while (ft_isalpha(g->tokens[n].arg[0][i]) == 0
			&& g->tokens[n].arg[0][i] != '\0')
			i++;
		if (g->tokens[n].arg[0][i] == '\0')
			exit(ft_atoi(g->tokens[n].arg[0]));
		else
		{
			ft_putstr_fd(" numeric argument required", 2);
			exit (2);
		}
	}
	exit(0);
}
