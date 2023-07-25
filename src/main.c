#include "../include/minishell.h"

int	main(void)
{
	char		*input;
	t_global	*global;
	int			i;

	global = init_struct();
	i = 0;
	while (i < 1)
	{
		rl_on_new_line();
		//input = readline(">> ");
		input = ft_strdup("| ls | cat -e 'hola ");
		add_and_store_history(input);
		get_struct_data(global, input);
		printf("\ninput =\t%s\n", global->input);
		if (ft_strncmp(input, "exit", 5) == 0)
			exit (0);
		i++;
	}
	return (0);
}
