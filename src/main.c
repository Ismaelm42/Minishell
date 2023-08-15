#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_global	*global;
	int			sign;

	sign = 1;
	(void)argc;
	(void)argv;
	global = init_struct(env);
	while (1)
	{
		signal(SIGINT, ft_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		rl_on_new_line();
		input = readline(">> ");
		if (!input)
		{
			printf("%d", sign);
			sign = control_d(input);
		}
		//input = ft_strdup("hola1 hola2 hola3 |");
		else
		{
			add_and_store_history(input);
			if (ft_strncmp(input, "exit", 5) == 0)
			{
				//destroy_global(global);
				exit (0);
			}
			if (local_var(global, input) == 1)
				get_struct_data(global, input);
			//printf("%s", global->tokens[0].command);
			
			// if (ft_strncmp(global->tokens[0].command, "pwd", 3))
			//ft_pwd();
			//ft_env(global);
		}

	}
	// 	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_global	*global;

// 	(void)argc;
// 	(void)argv;
// 	global = init_struct(env);
// 	rl_catch_signals = 0;

// 	//input = ft_strdup("ARG=\"HOLA\"1>2'>>34'5\"678\"");
// 	//add_and_store_history(input);
// 	//(void)global;
// 	//get_struct_data(global, input);
// 	//local_var(input);
// 	// printf("diccinario de locales\n");
// 	// print_stack(global->lst_local);
// 	//search_key_and_replace(global->lst_env, "_", "NIEBLA");
// 	//printf("Valor de _: %s\n", search_key(global->lst_env, "_"));

// 	while (1)
// 	{
// 		signal(SIGINT, ft_sigint_handler);
// 		signal(SIGQUIT, SIG_IGN);
// 		global->input = readline("> ");
// 		add_and_store_history(global->input);
// 		local_var(global);
// 		rl_on_new_line();
// 		if (!global->input)
// 			control_d(global->input);
// 		if (ft_strncmp(global->input, "exit", 4) == 0)
// 		{
// 			free (global->input);
// 			exit(0);
// 		}
// 	}
// }



