#include "../../include/minishell.h"

int	handle_infiles(char *infile, int write_flag, int type_flag, int infile_type)
{
	int	fd_file;


	infile_type = 0 + infile_type;
	if (type_flag < 0)
	{
		
	}
	else if (type_flag == 1)
		fd_file = open(infile, O_RDONLY, 0666);
	if (fd_file == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(infile, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		close(fd_file);
		return (1);
	}
	if (write_flag == 1)
	{
		if (dup2(fd_file, STDIN_FILENO) == -1)
			return (ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd_file);
	return (0);
}

int	detect_input_file(char **infiles, int type_flag, int infile_type)
{
	int	i;
	int	write_flag;

	i = 0;
	write_flag = 0;
	while (infiles[i] != NULL)
	{
		if (infiles[i + 1] == NULL && ((type_flag == infile_type)
				|| (type_flag == -1 && infile_type < 0)))
			write_flag = 1;
		if (handle_infiles(infiles[i], write_flag, type_flag, infile_type) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	get_infile(t_global *global, int n)
{
	int	infile_type;

	infile_type = global->tokens[n].fd_in;
	if (detect_input_file(global->tokens[n].heredoc, -1, infile_type) != 0)
		return (1);
	if (detect_input_file(global->tokens[n].infile, 1, infile_type) != 0)
		return (1);
	return (0);
}
