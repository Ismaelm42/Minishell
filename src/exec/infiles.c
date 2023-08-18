#include "../../include/minishell.h"

int	exec_heredoc(char ***infiles, char *buffer, int fd_type, int fd)
{
	while (1)
	{
		buffer = readline("");
		if (buffer != NULL)
		{
			if (ft_strncmp(buffer, **infiles, ft_strlen(**infiles) + 1) == 0
				&& (*infiles)[1] == NULL)
			{
				free(buffer);
				break ;
			}
			if (ft_strncmp(buffer, **infiles, ft_strlen(**infiles) + 1) == 0
				&& (*infiles)[1] != NULL)
				(*infiles)++;
			else if ((*infiles)[1] == NULL && fd_type < 0)
			{
				ft_putstr_fd(buffer, fd);
				ft_putstr_fd("\n", fd);
			}
		}
		free(buffer);
		buffer = NULL;
	}
	return (0);
}

int	handle_heredoc(char ***infiles, int fd_type)
{
	char			*buffer;
	int				fd;

	buffer = NULL;
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return ((close(fd), ft_putstr_fd(strerror(errno), 2), 1));
	exec_heredoc(infiles, buffer, fd_type, fd);
	close(fd);
	if (open(".heredoc", O_RDONLY, 0666) == -1)
		return ((close(fd), ft_putstr_fd(strerror(errno), 2), 1));
	if ((*infiles)[1] == NULL && fd_type < 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd);
	return (0);
}

int	handle_infile_and_heredoc(char ***infiles, int infile_type, int fd_type)
{
	int	fd_file;

	if (infile_type < 0)
		return (handle_heredoc(infiles, fd_type));
	else
	{
		fd_file = open(**infiles, O_RDONLY, 0666);
		if (fd_file == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(**infiles, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (close(fd_file), 1);
		}
		if ((*infiles)[1] == NULL && fd_type == 1)
		{
			if (dup2(fd_file, STDIN_FILENO) == -1)
				return (close(fd_file), ft_putstr_fd(strerror(errno), 2), 1);
		}
		close(fd_file);
	}
	return (0);
}

int	get_infile(t_global *global, int n)
{
	int	fd_type;

	fd_type = global->tokens[n].fd_in;
	while (*global->tokens[n].heredoc != NULL)
	{
		if (handle_infile_and_heredoc \
		(&global->tokens[n].heredoc, -1, fd_type) != 0)
			return (1);
		global->tokens[n].heredoc++;
	}
	while (*global->tokens[n].infile != NULL)
	{
		if (handle_infile_and_heredoc \
		(&global->tokens[n].infile, 1, fd_type) != 0)
			return (1);
		global->tokens[n].infile++;
	}
	return (0);
}

int	fd_in_handler(t_global *global, int n, int fd_in, int fd_out)
{
	if (global->tokens[n].fd_in != 0)
	{
		if (get_infile(global, n) != 0)
			return (close(fd_in), close(fd_out), 1);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd_in);
	return (0);
}
