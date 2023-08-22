#include "../../include/minishell.h"

int	handle_outfiles(char *outfile, int write_flag, int infile_type)
{
	int	fd;

	if (infile_type == -1)
		fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (infile_type == 1)
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		print_error(outfile, errno);
		return (close(fd), 1);
	}
	if (write_flag == 1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (print_error("pipeline error", errno), 1);
	}
	close(fd);
	return (0);
}

int	detect_output_file(char **outfiles, int infile_type, int fd_type)
{
	int	i;
	int	write_flag;

	i = 0;
	write_flag = 0;
	while (outfiles[i] != NULL)
	{
		if (outfiles[i + 1] == NULL && infile_type == fd_type)
			write_flag = 1;
		if (handle_outfiles(outfiles[i], write_flag, infile_type) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_output_file(t_global *global, int n)
{
	int	fd_type;

	fd_type = global->tokens[n].fd_out;
	if (detect_output_file(global->tokens[n].append, -1, fd_type) != 0)
		return (1);
	if (detect_output_file(global->tokens[n].outfile, 1, fd_type) != 0)
		return (1);
	return (0);
}

int	fd_out_handler(t_global *global, int n, int fd_out)
{
	if (global->tokens[n].fd_out != 0)
	{
		if (get_output_file(global, n) != 0)
			return (close(fd_out), 1);
	}
	else
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (print_error("pipeline error", errno), 1);
	}
	close(fd_out);
	return (0);
}
