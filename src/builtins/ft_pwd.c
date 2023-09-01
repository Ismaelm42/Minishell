#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
		ft_putstr_fd("minishell: pwd error\n", 2);
	else
	{
		ft_putstr_fd(dir, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free_mem((void **)&dir);
	}
}
