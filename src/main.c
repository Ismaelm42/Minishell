#include "../include/minishell.h"

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

int	main(void)
{
	char	*input;

	while (1)
	{
		rl_on_new_line();
		input = readline(">> ");
		if (add_and_store_history(input) == 1)
			clean_up_and_exit(EXIT_FAILURE, input);
		if (ft_strncmp(input, "exit", 5) == 0)
			clean_up_and_exit(EXIT_SUCCESS, input);
		free(input);
	}
	return (0);
}
