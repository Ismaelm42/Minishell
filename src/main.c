#include "../include/minishell.h"

char	*expansion_variable(char *input)
{
	t_tokens	*tokens;
	int			size;
	int			i;

	tokens = get_variable_expansion_tokens(input);
	size = variable_expansion_counter(input);
	i = 0;
	while (i < size)
	{
		get_variable_expansion_value(i, tokens);
		// printf("tokens_var[%d] = %s\n", i, tokens[i].variable);
		// printf("tokens_exp[%d] = %s\n\n", i, tokens[i].expanded);
		i++;
	}
	replace_variables(input, tokens);
	return (input);
}

// int	main(void)
// {
// 	char	*input;
// 	int		i;

// 	i = 0;
// 	while (i < 1)
// 	{
// 		rl_on_new_line();
// 		//input = readline(">> ");
// 		input = ft_strdup("$12345$$${HOME} $ $NOEXIST ${ARG} $PATH $ARG>outfile");
// 		if (add_and_store_history(input) == 1)
// 			clean_up_and_exit(EXIT_FAILURE, input);
// 		expansion_variable(input);
// 		if (ft_strncmp(input, "exit", 5) == 0)
// 			clean_up_and_exit(EXIT_SUCCESS, input);
// 		free(input);
// 		i++;
// 	}
// 	return (0);
// }



