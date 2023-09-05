#include "../../include/minishell.h"

void	handle_heredocs(t_global *global, int n)
{
	char	*heredoc;
	int		fd;

	heredoc = ft_strjoin("/tmp/.heredoc", ft_itoa(n), 2);
	fd = open(heredoc, O_RDONLY, 0666);
	if (fd == -1)
	{
		print_error(heredoc, errno);
		free_mem((void **)&heredoc);
		free_global(global, 1);
		exit (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		free_mem((void **)&heredoc);
		free_global(global, 1);
		print_error("Pipeline error", errno);
		exit(-1);
	}
	close(fd);
	free_mem((void **)&heredoc);
}

void	handle_infiles(t_global *global, char ***infiles, int fd_type)
{
	int	fd_file;

	fd_file = open(**infiles, O_RDONLY, 0666);
	if (fd_file == -1)
	{
		print_error(**infiles, errno);
		free_global(global, 1);
		exit (1);
	}
	if ((*infiles)[1] == NULL && fd_type == 1)
	{
		if (dup2(fd_file, STDIN_FILENO) == -1)
		{
			free_global(global, 1);
			print_error("Pipeline error", errno);
			exit (-1);
		}
	}
	close(fd_file);
}

void	get_input_file(t_global *global, int n)
{
	int		fd_type;

	fd_type = global->tokens[n].fd_in;
	while (*global->tokens[n].infile != NULL)
	{
		handle_infiles(global, &global->tokens[n].infile, fd_type);
		global->tokens[n].infile++;
	}
	if (fd_type < 0)
		handle_heredocs(global, n);
}

void	fd_in_handler(t_global *global, int n)
{
	if (global->tokens[n].fd_in != 0)
		get_input_file(global, n);
	else
	{
		if (n != 0)
		{
			if (dup2(global->fd[n][0], STDIN_FILENO) == -1)
			{
				free_global(global, 1);
				print_error("Pipeline error", errno);
				exit(-1);
			}
		}
	}
	close(global->fd[n][0]);
}
