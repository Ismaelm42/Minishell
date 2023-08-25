#include "../../include/minishell.h"

void	get_heredocs(char **heredoc, int fd)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("");
		if (buffer != NULL)
		{
			if (ft_strncmp(buffer, *heredoc, ft_strlen(*heredoc) + 1) == 0
				&& heredoc[1] == NULL)
			{
				free_mem((void **)&buffer);
				break ;
			}
			if (ft_strncmp(buffer, *heredoc, ft_strlen(*heredoc) + 1) == 0
				&& heredoc[1] != NULL)
				heredoc++;
			else if (heredoc[1] == NULL)
			{
				ft_putstr_fd(buffer, fd);
				ft_putstr_fd("\n", fd);
			}
		}
		free_mem((void **)&buffer);
	}
}

int	process_heredocs(t_global *global)
{
	char	*heredoc;
	int		fd;
	int		n;

	n = 0;
	while (n < global->pipeline)
	{
		if (global->tokens[n].heredoc[0] != NULL)
		{
			heredoc = ft_strjoin(".heredoc", ft_itoa(n), 2);
			fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
				return (print_error("heredoc", errno), 1);
			free_mem((void **)&heredoc);
			get_heredocs(global->tokens[n].heredoc, fd);
			close(fd);
		}
		n++;
	}
	return (0);
}
