#include "../../include/minishell.h"

void	ft_pwd(int newline, int colour)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
	{
		ft_putstr_fd("pwd error", 2);
		ft_putchar_fd('\n', 2);
	}
	if (colour == 1)
		ft_putstr_fd("\033[0;36m", STDOUT_FILENO);
	ft_putstr_fd(dir, STDOUT_FILENO);
	if (colour == 1)
		ft_putstr_fd("\x1b[0m", STDOUT_FILENO);
	if (newline == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	free(dir);
}
