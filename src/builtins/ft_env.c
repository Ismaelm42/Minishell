#include "../../include/minishell.h"

void	ft_env(t_global *g)
{
	int	i;

	i = 0;
	while (g->env[i] != NULL)
	{
		printf("%s\n", g->env[i]),
		i++;
	}
}
