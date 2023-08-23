#include "../../../include/minishell.h"

/*
Libera la memoria reservada en caso de fallo.
*/
char	**free_matrix(char **matrix)
{
	int	n;

	n = 0;
	if (matrix != NULL)
	{
		while (matrix[n] != NULL)
		{
			free(matrix[n]);
			matrix[n] = NULL;
			n++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (NULL);
}

/*
Elimina la estructura global por completo.
*/
void	destroy_global(t_global *global)
{
	if (global->input != NULL)
		free(global->input);
	free_env(global->env);
	ft_free_lst(global->lst_local);
	free(global);
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
		free_matrix(global->tokens[n].infile);
		free_matrix(global->tokens[n].outfile);
		free_matrix(global->tokens[n].heredoc);
		free_matrix(global->tokens[n].append);
		if (global->tokens[n].command != NULL)
			free(global->tokens[n].command);
		free_matrix(global->tokens[n].arg);
		n++;
	}
	if (global->tokens != NULL)
	{
		free(global->tokens);
		global->tokens = NULL;
	}
	// if (global->input != NULL)
	// 	free(global->input);
	global->pipeline = 0;
	if (flag == 1)
		destroy_global(global);
}

// void	print_result(t_token *tokens, int *size)
// {
// 	int	i;

// 	i = 0;
// 	(void)size;
// 	while (tokens->infile[i] != NULL)
// 	{
// 		printf("tokens->infile[%d] = %s\n", i, tokens->infile[i]);
// 		i++;
// 	}
// 	// printf("size->infile = %d\n", size[0]);
// 	// printf("\n");

// 	i = 0;
// 	while (tokens->outfile[i] != NULL)
// 	{
// 		printf("tokens->outfile[%d] = %s\n", i, tokens->outfile[i]);
// 		i++;
// 	}
// 	// printf("size->outfile = %d\n", size[1]);
// 	// printf("\n");

// 	i = 0;
// 	while (tokens->heredoc[i] != NULL)
// 	{
// 		printf("tokens->heredoc[%d] = %s\n", i, tokens->heredoc[i]);
// 		i++;
// 	}
// 	// printf("size->heredoc = %d\n", size[2]);
// 	// printf("\n");

// 	i = 0;
// 	while (tokens->append[i] != NULL)
// 	{
// 		printf("tokens->append[%d] = %s\n", i, tokens->append[i]);
// 		i++;
// 	}
// 	// printf("size->append = %d\n", size[3]);
// 	// printf("\n");

// 	printf("tokens->command = %s\n", tokens->command);
// 	// printf("\n");

// 	i = 0;
// 	while (tokens->arg[i] != NULL)
// 	{
// 		printf("tokens->arg[%d] = %s\n", i, tokens->arg[i]);
// 		i++;
// 	}
// 	// printf("size->arg = %d\n", size[5]);
// 	printf("\n");
// 	printf("\n");
// }
