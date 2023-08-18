#include "../../include/minishell.h"

int	heredoc(char ***infiles, int fd_type)
{
	char			*buffer;
	int				fd_heredoc;

	fd_heredoc = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
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
				ft_putstr_fd(buffer, fd_heredoc);
				ft_putstr_fd("\n", fd_heredoc);
			}
		}
		free(buffer);
		buffer = NULL;
	}
	close(fd_heredoc);
	open(".heredoc", O_RDONLY, 0666);
	if ((*infiles)[1] == NULL && fd_type < 0)
	{
		if (dup2(fd_heredoc, STDIN_FILENO) == -1)
			return (close(fd_heredoc), ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd_heredoc);
	return (0);
}

int	handle_infiles(char ***infiles, int infile_type, int fd_type)
{
	int	fd_file;

	if (infile_type < 0)
		return (heredoc(infiles, fd_type));
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
			printf("AQUINOSEENTRA VERDAD?\n");
			if (dup2(fd_file, STDIN_FILENO) == -1)
				return (close(fd_file), ft_putstr_fd(strerror(errno), 2), 1);
		}
		close(fd_file);
	}
	return (0);
}

int	detect_input_file(char **infiles, int infile_type, int fd_type)
{
	while (*infiles != NULL)
	{
		if (handle_infiles(&infiles, infile_type, fd_type) != 0)
			return (1);
		infiles++;
	}
	return (0);
}

int	get_infile(t_global *global, int n)
{
	int	fd_type;

	fd_type = global->tokens[n].fd_in;
	if (detect_input_file(global->tokens[n].heredoc, -1, fd_type) != 0)
		return (1);
	if (detect_input_file(global->tokens[n].infile, 1, fd_type) != 0)
		return (1);
	return (0);
}
