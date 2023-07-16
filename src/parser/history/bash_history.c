#include "../../../include/minishell.h"

void	clean_up_and_exit(int status, char *ptr)
{
	free(ptr);
	rl_clear_history();
	unlink(".bash_history");
	exit(status);
}

int	add_and_store_history(char *input)
{
	int		fd_history;

	add_history(input);
	fd_history = open(".bash_history", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_history == -1)
	{
		ft_putstr_fd("Error creating command history file", 2);
		return (1);
	}
	ft_putstr_fd(input, fd_history);
	ft_putchar_fd('\n', fd_history);
	return (0);
}
