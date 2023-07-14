#include "../../../include/minishell.h"

int	main(void)
{
	t_tokens	*tokens;
	char		*str = "$12345$$${HOME} $ $NOEXIST ${ARG} $PATH $ARG>outfile";
	int			size;

	size = variable_expansion_counter(str);
	tokens = get_variable_expansion_tokens(str);

	int i = 0;
	while (i < size)
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
