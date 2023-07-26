#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_global	*global;
	int			i;

	(void)argc;
	(void)argv;
	global = init_struct(env);
	i = 0;
	while (i < 1)
	{
		rl_on_new_line();
		//input = readline(">> ");
		input = ft_strdup("ls | cat -e | $HOME");
		add_and_store_history(input);
		get_struct_data(global, input);
		printf("\ninput =\t%s\n", global->input);
		if (ft_strncmp(input, "exit", 5) == 0)
			exit (0);
		i++;
	}
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	//char	*input;
// 	//t_node	*lst_env;

// 	(void)argc;
// 	(void)argv;
// 	lst_env = init_list();
// 	lst_locals = init_list();
// 	rl_catch_signals = 0;
// 	copy_environment(env);
// 	print_stack(lst_env);
// 	printf("Valor de LESSOPEN : %s\n", search_key(lst_env, "LESSOPEN"));
// 	printf("Valor de _: %s\n", search_key(lst_env, "_"));
// 	search_key_and_replace(lst_env, "_", "NIEBLA");
// 	printf("Valor de _: %s\n", search_key(lst_env, "_"));

// 	// while (1)
// 	// {
// 	// 	signal(SIGINT, ft_sigint_handler);
// 	// 	signal(SIGQUIT, SIG_IGN);
// 	// 	input = readline("> ");
// 	// 	rl_on_new_line();
// 	// 	if (!input)
// 	// 		control_d(input);
// 	// 	if (ft_strncmp(input, "exit", 4) == 0)
// 	// 	{
// 	// 		free (input);
// 	// 		exit(0);
// 	// 	}
// 	// }
// }