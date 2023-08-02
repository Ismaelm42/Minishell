#include "../../../include/minishell.h"

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
