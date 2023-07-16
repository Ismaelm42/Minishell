#include "../include/minishell.h"

/*
Se encarga de realizar todo el procedimiento para expandir la variable $.
En esta función, se realizan todas las demás de la carpeta src/expand_variables.
Una vez realizada la llamada a esta función, obtenemos un nuevo input modificado
con los valores reales de $.
*/
char	*expansion_variable(char *input)
{
	t_tokens	*tokens;
	char		*new_input;
	int			size;
	int			i;

	tokens = get_variable_expansion_tokens(input);
	size = variable_expansion_counter(input);
	i = 0;
	while (i < size)
	{
		get_variable_expansion_value(i, tokens);
		i++;
	}
	new_input = replace_variables(input, tokens);
	free(input);
	if (search_for_more_sign_dollars(new_input) == 1)
		new_input = expansion_variable(new_input);
	return (new_input);
}

int	main(void)
{
	char	*input;
	int		i;

	i = 0;
	while (i < 1)
	{
		rl_on_new_line();
		//input = readline(">> ");
		input = ft_strdup("$$ $ $12345 $ARG ${ARG}|$HOME ${LOGNAME} $PWD $NOARG");
		printf("%s\n", input);
		if (add_and_store_history(input) == 1)
			clean_up_and_exit(EXIT_FAILURE, input);
		input = expansion_variable(input);
		printf("%s\n", input);
		if (ft_strncmp(input, "exit", 5) == 0)
			clean_up_and_exit(EXIT_SUCCESS, input);
		free(input);
		i++;
	}
	return (0);
}
