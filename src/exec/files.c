/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:41:39 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:43:38 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char		*extract_infile(t_global *global, int n, int i);
static void		handle_infile(t_global *global, int n, int i);
static void		handle_outfile(t_global *global, int n, int i);
static void		check_files(t_global *global, int n);

static char	*extract_infile(t_global *global, int n, int i)
{
	char	*file;

	if (ft_strncmp(global->tokens[n].file[i - 1], "<", 2) == 0)
		file = ft_strdup(global->tokens[n].file[i]);
	else
		file = ft_strjoin("/tmp/.heredoc", ft_itoa(n), 2);
	return (file);
}

static void	handle_infile(t_global *global, int n, int i)
{
	char	*file;
	int		fd_file;

	file = extract_infile(global, n, i);
	fd_file = open(file, O_RDONLY, 0666);
	if (fd_file == -1)
	{
		print_error(file, errno);
		free_mem((void **)&file);
		free_global(global, 1);
		exit (1);
	}
	if (*(search_next_file(&global->tokens[n].file[i], "<")) == NULL
		&& *(search_next_file(&global->tokens[n].file[i], "<<")) == NULL)
	{
		if (dup2(fd_file, STDIN_FILENO) == -1)
		{
			free_mem((void **)&file);
			free_global(global, 1);
			print_error("Pipeline error", errno);
			exit (-1);
		}
	}
	free_mem((void **)&file);
	close(fd_file);
}

static void	handle_outfile(t_global *global, int n, int i)
{
	int	fd;

	if (ft_strncmp(global->tokens[n].file[i - 1], ">", 2) == 0)
		fd = open(global->tokens[n].file[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(global->tokens[n].file[i], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(global->tokens[n].file[i], errno);
		free_global(global, 1);
		exit(1);
	}
	if (*(search_next_file(&global->tokens[n].file[i], ">")) == NULL
		&& *(search_next_file(&global->tokens[n].file[i], ">>")) == NULL)
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

static void	check_files(t_global *global, int n)
{
	int	ret_dup2_infile;
	int	ret_dup2_outfile;

	ret_dup2_infile = 0;
	ret_dup2_outfile = 0;
	if (*(search_next_file(global->tokens[n].file, "<")) == NULL
		&& *(search_next_file(global->tokens[n].file, "<<")) == NULL)
	{
		if (n != 0)
			ret_dup2_infile = dup2(global->fd[n][0], STDIN_FILENO);
	}
	if (*(search_next_file(global->tokens[n].file, ">")) == NULL
		&& *(search_next_file(global->tokens[n].file, ">>")) == NULL)
	{
		if (global->pipeline > 1 && n != (global->pipeline - 1))
			ret_dup2_outfile = dup2(global->fd[n + 1][1], STDOUT_FILENO);
	}
	if (ret_dup2_infile == -1 || ret_dup2_outfile == -1)
	{
		free_global(global, 1);
		print_error("Pipeline error", errno);
		exit(-1);
	}
}

void	handle_files(t_global *global, int n)
{
	int	i;

	i = 0;
	check_files(global, n);
	while (global->tokens[n].file[i] != NULL)
	{
		if (ft_strncmp(global->tokens[n].file[i], "<", 1) == 0)
			handle_infile(global, n, ++i);
		else if (ft_strncmp(global->tokens[n].file[i], ">", 1) == 0)
			handle_outfile(global, n, ++i);
		i++;
	}
	close(global->fd[n][0]);
	close(global->fd[n + 1][1]);
}
