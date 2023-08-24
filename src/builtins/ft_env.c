#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	if (g->env[0] == NULL)
		ft_putstr_fd("error", 2);
	while (g->env[i] != NULL)
	{
		ft_putstr_fd(g->env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
