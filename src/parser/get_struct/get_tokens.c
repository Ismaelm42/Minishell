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
	printf("size = %d\n", size + 1);
	return (size + 1);
}

t_token	*get_tokens(char *input)
{
	t_token	*tokens;
	char	**lexer;
	int		n;

	lexer = get_lexer(input);
	if (syntax_error_check(lexer) == -1)
		return (NULL);
	n = lexer_pipes_counter(lexer);
	tokens = (t_token *)calloc(sizeof(t_token), n + 1);
	return (tokens);
}
