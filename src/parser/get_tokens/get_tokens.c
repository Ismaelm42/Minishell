#include "../../../include/minishell.h"

char	**get_tokens(char *input)
{
	char	*new_input;
	char	**tokens;

	new_input = expansion_variable(input);
	printf("%s\n\n", new_input);
	tokens = token_maker(new_input);
	free(new_input);
	return (tokens);
}
