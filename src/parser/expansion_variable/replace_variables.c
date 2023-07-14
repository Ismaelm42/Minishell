#include "../../../include/minishell.h"

int	main(void)
{
	t_tokens	*tokens;
	char		*str = "$$${HOME} $babalu ${HOME} $ARG";

	tokens = get_variable_expansion_tokens(str);

	int i = 0;
	while (i < 4)
	{
		get_variable_expansion_value(i, tokens);
		printf("tokens_var[%d] = %s\n", i, tokens[i].variable);
		printf("tokens_exp[%d] = %s\n\n", i, tokens[i].expanded);
		i++;
	}
	printf("tokens_var[%d] = %s\n", i, tokens[i].variable);
	printf("tokens_exp[%d] = %s\n", i, tokens[i].expanded);
	return (0);

}
