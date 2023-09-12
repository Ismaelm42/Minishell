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
	if (ft_strncmp(**lexer, "<", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, ">", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, "<<", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, ">>", ft_strlen(**lexer)) == 0)
	{
		(*size)[0]++;
		(*lexer)++;
	}
	else if ((*size)[1] == 0)
		(*size)[1]++;
	else
		(*size)[2]++;
}

/*
Se encarga de contar el número de tokens total para la reserva de memoria.
*/
int	*token_counter(char **lexer)
{
	int	*size;

	size = (int *)ft_calloc(sizeof(int), 3);
	while (*lexer != NULL && ft_strncmp(*lexer, "|", ft_strlen(*lexer)) != 0)
	{
		redirection_and_command_token_counter(&lexer, &size);
		lexer++;
	}
	return (size);
}
