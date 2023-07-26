#include "../../../include/minishell.h"

char	**get_lexer(char *input, t_global *global)
{
	char	*new_input;
	char	**lexer;

	new_input = expansion_variable(input, global);
	lexer = lexer_maker(new_input);
	int i = 0;
	printf("\n\n\n\n\n");
	while (lexer[i] != NULL)
	{
		printf("lexer[%d]= %s\n", i, lexer[i]);
		i++;
	}
	printf("\n\n\n\n\n");
	free(new_input);
	return (lexer);
}
