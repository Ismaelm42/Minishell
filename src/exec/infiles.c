#include "../../include/minishell.h"

int	handle_heredocs(int n)
{
	char	*heredoc;
	int		fd;

	heredoc = ft_strjoin(".heredoc", ft_itoa(n), 2);
	fd = open(heredoc, O_RDONLY, 0666);
	if (fd == -1)
		return (print_error("heredoc", errno), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		free(heredoc);
		print_error("Pipeline error6", errno);
		return (1);
	}
	close(fd);
	free(heredoc);
	return (0);
}

int	handle_infiles(char ***infiles, int fd_type)
{
	int	fd_file;

	fd_file = open(**infiles, O_RDONLY, 0666);
	if (fd_file == -1)
	{
		print_error(**infiles, errno);
		return (close(fd_file), 1);
	}
	if ((*infiles)[1] == NULL && fd_type == 1)
	{
		if (dup2(fd_file, STDIN_FILENO) == -1)
			return (close(fd_file), print_error("Pipeline error5", errno), 1);
	}
	close(fd_file);
	return (0);
}

int	get_input_file(t_global *global, int n)
{
	int		fd_type;

	fd_type = global->tokens[n].fd_in;
	while (*global->tokens[n].infile != NULL)
	{
		if (handle_infiles(&global->tokens[n].infile, fd_type) != 0)
			return (1);
		global->tokens[n].infile++;
	}
	if (fd_type < 0)
		return (handle_heredocs(n));
	return (0);
}

int	fd_in_handler(t_global *global, int n, int fd_in, int fd_out)
{
	if (global->tokens[n].fd_in != 0)
	{
		if (get_input_file(global, n) != 0)
			return (close(fd_in), close(fd_out), 1);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (print_error("Pipeline error4", errno), 1);
	}
	return (0);
}
