#include "../../include/minishell.h"

void	handle_outfiles(t_global *global, char *outfile, int write_flag, int infile_type)
{
	int	fd;

	if (infile_type == -1)
		fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (infile_type == 1)
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		free_global(global, 1);
		print_error(outfile, errno);
		exit(1);
	}
	if (write_flag == 1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			free_global(global, 1);
			print_error("Pipeline error", errno);
			exit(-1);
		}
	}
	close(fd);
}

void	detect_output_file(t_global *global, char **outfiles, int infile_type, int fd_type)
{
	int	i;
	int	write_flag;

	i = 0;
	write_flag = 0;
	while (outfiles[i] != NULL)
	{
		if (outfiles[i + 1] == NULL && infile_type == fd_type)
			write_flag = 1;
		handle_outfiles(global, outfiles[i], write_flag, infile_type);
		i++;
	}
}

void	get_output_file(t_global *global, int n)
{
	int	fd_type;

	fd_type = global->tokens[n].fd_out;
	detect_output_file(global, global->tokens[n].append, -1, fd_type);
	detect_output_file(global, global->tokens[n].outfile, 1, fd_type);
}

void	fd_out_handler(t_global *global, int n)
{
	if (global->tokens[n].fd_out != 0)
		get_output_file(global, n);
	else
	{
		if (global->pipeline > 1 && n != (global->pipeline - 1))
		{
			if (dup2(global->fd[n + 1][1], STDOUT_FILENO) == -1)
			{
				free_global(global, 1);
				print_error("Pipeline error", errno);
				exit(-1);
			}
		}
	}
	close(global->fd[n + 1][1]);
}
