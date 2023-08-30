#include "../../include/minishell.h"

char	*get_home_dir(char *dir)
{
	char	*home;

	if (ft_strnstr(dir, "/home/", 6) != NULL && ft_strlen(dir) > 6)
	{
		home = ft_strchr((char *)&dir[7], '/');
		if (home == NULL && ft_strlen(dir) > 6)
		{
			home = ft_strdup("~");
			return (free(dir), home);
		}
		if (home != NULL)
		{
			home = ft_strjoin("~", home, 0);
			return (free(dir), home);
		}
	}
	return (dir);
}

void	ft_pwd(int newline_flag, int colour_flag, int home_flag)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (home_flag == 1)
		dir = get_home_dir(dir);
	if (dir == NULL)
		ft_putstr_fd("minishell: pwd error\n", 2);
	if (colour_flag == 1)
		ft_putstr_fd("\033[0;36m", STDOUT_FILENO);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\x1b[0m", STDOUT_FILENO);
	if (newline_flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	free(dir);
}
