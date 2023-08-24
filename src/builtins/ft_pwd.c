#include "../../include/minishell.h"

void	ft_pwd(int fd_in, int fd_out)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	fd_in = fd_in + 0;
	fd_out = fd_out + 0;
	if (dir == NULL)
	{
		ft_putstr_fd("pwd error", 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putstr_fd(dir, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(dir);
}
