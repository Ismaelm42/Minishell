#include "../../include/minishell.h"

void	get_heredocs(t_global *global, char **heredoc, int fd)
{
	char	*buffer;

	signal(SIGINT, ft_sigint_heredoc);
	while (1)
	{
		buffer = readline("");
		if (buffer == NULL)
			control_d(global, buffer);
		if (buffer != NULL)
		{
			if (ft_strncmp(buffer, *heredoc, ft_strlen(*heredoc) + 1) == 0
				&& *(search_next_file(heredoc, "<<")) == NULL)
			{
				free_mem((void **)&buffer);
				break ;
			}
			if (ft_strncmp(buffer, *heredoc, ft_strlen(*heredoc) + 1) == 0
				&& *(search_next_file(heredoc, "<<")) != NULL)
					heredoc = search_next_file(heredoc, "<<");
			else if (*(search_next_file(heredoc, "<<")) == NULL)
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
	char	*heredoc_name;
	int		fd;

	if (*(search_next_file(global->tokens[n].file, "<<")) != NULL)
	{
		heredoc_name = ft_strjoin("/tmp/.heredoc", ft_itoa(n), 2);
		fd = open(heredoc_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			print_error("heredoc", errno);
			free_mem((void **)&heredoc_name);
			free_global(global, 1);
			exit(1);
		}
		free_mem((void **)&heredoc_name);
		get_heredocs(global, \
		search_next_file(global->tokens[n].file, "<<"), fd);
		close(fd);
	}
	free_mem((void **)&global->pid);
	free_global(global, 1);
	exit(0);
}

int	process_heredocs(t_global *global)
{
	int		n;

	global->pid = (pid_t *)ft_calloc(sizeof(pid_t), global->pipeline);
	n = 0;
	while (n < global->pipeline)
	{
		signal(SIGINT, SIG_IGN);
		global->pid[n] = fork();
		if (global->pid[n] == -1)
		{
			global->exit_status = -1;
			return (print_error("Fork error", errno), 1);
		}
		if (global->pid[n] == 0)
			heredoc_child_process(global, n);
		waitpid(global->pid[n], &global->exit_status, 0);
		if (WIFEXITED(global->exit_status))
			global->exit_status = WEXITSTATUS(global->exit_status);
		if (global->exit_status != 0)
		{
			if (global->exit_status == 130)
				tcsetattr(STDIN_FILENO, TCSANOW, &global->prompt);
			return (1);
		}
		n++;
	}
	free_mem((void **)&global->pid);
	return (0);
}
