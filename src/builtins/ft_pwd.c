#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*dir;
//¿duda creo aki el fork o se crea en el executor?
	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
	{
		ft_putstr_fd("pwd error", 2);
		ft_putchar_fd('\n', 2);
	}
	printf("%s\n", dir);
	free(dir);
}
