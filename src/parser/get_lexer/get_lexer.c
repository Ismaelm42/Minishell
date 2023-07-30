#include "../../../include/minishell.h"

char	**get_lexer(char *input, t_global *global)
{
	char	*new_input;
	char	**lexer;

	new_input = expansion_variable(input, global);
	printf("new_input = %s\n", new_input);
	lexer = lexer_maker(new_input);
	free(new_input);
	return (lexer);
}
