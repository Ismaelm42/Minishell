#include "../../include/minishell.h"

void	ft_env(t_global *g, int fd_out)
{
	int	i;

	i = 0;
	while (g->env[i] != NULL)
	{
		ft_putstr_fd(g->env[i], fd_out);
		ft_putchar_fd('\n', fd_out);
		i++;
	}
}
