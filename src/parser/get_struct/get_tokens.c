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
Llama a la función get_lexer, y una vez obtenido el lexer, se utiliza para
reservar la memoria y guardar la información en la estructura tokens.
*/
int	get_tokens(char *input, t_global *global)
{
	t_token	*tokens;
	char	**lexer;
	int		return_n;
	int		n;

	lexer = get_lexer(input, global);
	return_n = syntax_error_check(lexer);
	if (return_n != 0)
		return (free_lexer(lexer), return_n);
	n = lexer_pipes_counter(lexer);
	tokens = (t_token *)ft_calloc(sizeof(t_token), n + 1);
	token_maker(tokens, lexer);
	global->pipeline = n;
	global->tokens = tokens;
	free_lexer(lexer);
	return (0);
}
