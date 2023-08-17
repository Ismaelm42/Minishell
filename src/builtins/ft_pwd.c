#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
	{
		ft_putstr_fd("pwd error", 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putstr_fd(dir, STDOUT_FILENO);
	//printf("%s \n", dir);
	printf("\nentra en building pwd\n");
	free(dir);
}
