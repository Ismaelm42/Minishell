#include "../../../include/minishell.h"

void	token_maker(t_token *tokens, char **lexer)
{
	int	*size;

	while (*lexer != NULL)
	{
		size = token_counter(lexer);
		allocate_token_memory(tokens, size);
		token_filler(tokens, lexer);
		advance_lexer_tokens(&lexer, &tokens);
	}
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
	if (lexer == NULL)
		return (1);
	return_n = syntax_error_check(lexer);
	if (return_n != 0)
		return (free_matrix((void ***)&lexer, 0), return_n);
	n = lexer_pipes_counter(lexer);
	tokens = (t_token *)ft_calloc(sizeof(t_token), n + 1);
	token_maker(tokens, lexer);
	global->pipeline = n;
	global->tokens = tokens;
	free_matrix((void ***)&lexer, 0);
	return (0);
}
