#include "../../../include/minishell.h"

/*
Cuenta el número de pipes que hay en el lexer para así saber cuánto memoria reservar.
Se suma uno más ya que el número de pipes es siempre igual a uno menos de la memoria
que se debe reservar. 
*/
int	lexer_pipes_counter(char **lexer)
{
	int	size;

	size = 0;
	while (*lexer != NULL)
	{
		if (*lexer[0] == '|')
			size++;
		lexer++;
	}
	return (size + 1);
}

/*
Recorre lexer y avanza su puntero dependiendo del contenido.
*/
void	redirection_and_command_token_counter(char ***lexer, int **size)
{
	if (ft_strncmp(**lexer, "<", ft_strlen(**lexer)) == 0)
	{
		(*size)[0]++;
		(*lexer)++;
	}
	else if (ft_strncmp(**lexer, ">", ft_strlen(**lexer)) == 0)
	{
		(*size)[1]++;
		(*lexer)++;
	}
	else if (ft_strncmp(**lexer, "<<", ft_strlen(**lexer)) == 0)
	{
		(*size)[2]++;
		(*lexer)++;
	}
	else if (ft_strncmp(**lexer, ">>", ft_strlen(**lexer)) == 0)
	{
		(*size)[3]++;
		(*lexer)++;
	}
	else if ((*size)[4] == 0)
		(*size)[4]++;
	else
		(*size)[5]++;
}

/*
Se encarga de contar el número de tokens total para la reserva de memoria.
*/
int	*token_counter(char **lexer)
{
	int	*size;

	size = (int *)ft_calloc(sizeof(int), 6);
	while (*lexer != NULL && ft_strncmp(*lexer, "|", ft_strlen(*lexer)) != 0)
	{
		redirection_and_command_token_counter(&lexer, &size);
		lexer++;
	}
	return (size);
}

//Esta función estudia el lexer para determinar cuál es el último file.
//Si el valor es -1, corresponderá con el heredoc o el append, 1 
//corresponde con el valor de infile, outfile y -2 es cuando tenemos un
//heredoc de doble entrada. De esta manera se podrá localizar fácilmente
//dónde está el último infile/outfile para poder realizar las operaciones
//necesarias en la parte ejecutora del código. 

void	check_last_token_file_fd(t_token *tokens, char **lexer, int n)
{
	int	i;

	i = n;
	while (--i >= 0 && ft_strncmp(lexer[i], "|", ft_strlen(lexer[i])) != 0)
	{
		if (ft_strncmp(lexer[i], "<<", 2) == 0 && tokens->fd_in == 0)
		{
			if (tokens->heredoc[1] == NULL)
				tokens->fd_in = -1;
			else
				tokens->fd_in = -2;
		}
		else if (ft_strncmp(lexer[i], "<", 2) == 0 && tokens->fd_in == 0)
			tokens->fd_in = 1;
		if (ft_strncmp(lexer[i], ">>", 2) == 0 && tokens->fd_out == 0)
			tokens->fd_out = -1;
		else if (ft_strncmp(lexer[i], ">", 2) == 0 && tokens->fd_out == 0)
			tokens->fd_out = 1;
	}
}

void	get_token_fd(t_token *tokens, char **lexer)
{
	int		i;
	int		n;

	i = 0;
	while (lexer[i] != NULL)
	{
		while (lexer[i] != NULL
			&& ft_strncmp(lexer[i], "|", strlen(lexer[i])) != 0)
			i++;
		n = i;
		check_last_token_file_fd(tokens, lexer, n);
		tokens++;
		if (lexer[i] != NULL)
			i++;
	}
}
