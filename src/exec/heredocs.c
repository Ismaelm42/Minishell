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

void	heredoc_child_process(t_global *global, int n)
{
	char	*heredoc;
	int		fd;

	if (global->tokens[n].heredoc[0] != NULL)
	{
		heredoc = ft_strjoin("/tmp/.heredoc", ft_itoa(n), 2);
		fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0666);
		free_mem((void **)&heredoc);
		if (fd == -1)
		{
			print_error(heredoc, errno);
			free_mem((void **)&heredoc);
			free_global(global, 1);
			exit(1);
		}
		get_heredocs(global->tokens[n].heredoc, fd);
		close(fd);
	}
	free_mem((void **)&global->pid);
	free_global(global, 1);
	exit(0);
}

int	process_heredocs(t_global *global)
{
	int		n;

	n = 0;
	global->pid = (pid_t *)ft_calloc(sizeof(pid_t), global->pipeline);
	while (n < global->pipeline)
	{
		global->pid[n] = fork();
		if (global->pid[n] == -1)
		{
			global->exit_status = -1;
			return (print_error("Fork error", errno), 1);
		}
		if (global->pid[n] == 0)
			heredoc_child_process(global, n);
		waitpid(global->pid[n], &global->exit_status, 0);
		n++;
	}
	free_mem((void **)&global->pid);
	return (0);
}
