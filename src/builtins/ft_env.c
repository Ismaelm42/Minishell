#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i] != NULL)
	{
		ft_putstr_fd(g->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
