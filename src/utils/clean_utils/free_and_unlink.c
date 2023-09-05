#include "../../../include/minishell.h"

void	unlink_files(int pipeline)
{
	char	*heredoc;
	int		n;

	n = 0;
	while (n < pipeline)
	{
		heredoc = ft_strjoin(".heredoc", ft_itoa(n), 2);
		if (access(heredoc, F_OK) == 0)
			unlink(heredoc);
		free_mem((void **)&heredoc);
		n++;
	}
}

void	free_mem(void **mem)
{
	if (*mem != 0)
		free(*mem);
	*mem = 0;
}

/*
Libera la memoria reservada en caso de fallo.
*/
char	**free_matrix(void ***matrix, int size)
{
	int	n;

	n = 0;
	if ((**matrix) != NULL)
	{
		if (size != 0)
			while (n < size)
				free_mem(&(*matrix)[n++]);
		else
			while ((*matrix)[n] != NULL)
				free_mem(&(*matrix)[n++]);
		free_mem((void **)&*matrix);
	}
	return (NULL);
}

/*
Elimina la estructura global por completo.
*/
void	destroy_global(t_global *global)
{
	free_matrix((void ***)&global->env, 0);
	ft_free_lst(global->lst_local);
	ft_free_lst(global->lst_env);
	free_mem((void **)&global);
}

/*
Libera eñ contenido de la estructura global para una nueva línea.
*/
void	free_global(t_global *global, int flag)
{
	int	n;

	n = 0;
	while (n < global->pipeline)
	{
		free_matrix((void ***)&global->tokens[n].infile, 0);
		free_matrix((void ***)&global->tokens[n].outfile, 0);
		free_matrix((void ***)&global->tokens[n].heredoc, 0);
		free_matrix((void ***)&global->tokens[n].append, 0);
		free_mem((void **)&global->tokens[n].command);
		free_matrix((void ***)&global->tokens[n].arg, 0);
		n++;
	}
	free_mem((void **)&global->tokens);
	free_mem((void **)&global->input);
	if (global->fd != NULL)
		free_matrix((void ***)&global->fd, global->pipeline + 1);
	free_mem((void **)&global->pid);
	unlink_files(global->pipeline);
	global->pipeline = 0;
	if (flag == 1)
		destroy_global(global);
}
