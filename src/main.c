#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_global	*global;

	(void)argc;
	(void)argv;
	global = init_struct(env);
	// while (1)
	// {
		// rl_on_new_line();
		// input = readline(">> ");
		// input = ft_strdup("ls -l | hola");
		// add_and_store_history(input);
		// get_struct_data(global, input);
		// free_global(global, 1);

		//input = ft_strdup("< infile1 grep >> infile3 > infile2  << a <<z q > infile4 | echo hola | >>infile3 grep bin |echo hola2");
		//con la línea >>infile3 grep bin falla, ver por qué, quizás no tenga ninguna entrada para ejecutar grep y se esté rayando
		//no entra en proceso padre porque se queda esperando al hijo. Quizás utilizar flag whonang por si se queda colgado????
		//revisar
		input = ft_strdup("< infile1 grep >> infile3 > infile2  << a <<z q > infile4 | echo hola | >>infile3 grep bin |echo hola2");
		add_and_store_history(input);
		get_struct_data(global, input);
		execute_commands(global);

		//free (input);
	// }
		return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*input;
// 	t_node	*lst_env;
// 	t_node	*lst_locals;

// 	(void)argc;
// 	(void)argv;
// 	lst_env = init_list();
// 	lst_locals = init_list();
// 	rl_catch_signals = 0;
// 	copy_environment(lst_env, env);
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


//controlar cuando es un input vacío.
