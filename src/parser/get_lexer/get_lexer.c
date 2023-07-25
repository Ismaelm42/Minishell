#include "../../../include/minishell.h"

char	**get_lexer(char *input)
{
	char	*new_input;
	char	**lexer;

	new_input = expansion_variable(input);
	lexer = lexer_maker(new_input);
	free(new_input);
	return (lexer);
}
