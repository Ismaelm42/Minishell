#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	if (g->env[0] == NULL)
		ft_putstr_fd("error", 2);
	while (g->env[i] != NULL)
	{
		printf("%s\n", g->env[i]),
		i++;
	}
}
