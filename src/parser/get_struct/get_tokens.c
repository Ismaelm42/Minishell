#include "../../../include/minishell.h"

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
		return (-3);
	return_n = syntax_error_check(lexer);
	if (return_n != 0)
		return (free_matrix((void ***)&lexer, 0), return_n);
	n = lexer_pipes_counter(lexer);
	tokens = (t_token *)ft_calloc(sizeof(t_token), n + 1);
	token_maker(tokens, lexer);
	get_token_fd(tokens, lexer);
	global->pipeline = n;
	global->tokens = tokens;
	free_matrix((void ***)&lexer, 0);
	return (0);
}
