#include "../../include/minishell.h"

 int	*g_status = 0;

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_global	*global;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	global = init_struct(env);
	g_status = &global->exit_status;
	while (1)
	{
		signal(SIGINT, ft_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline_prompt();
		if (!input)
			control_d(global, input);
		add_and_store_history(input);
		get_struct_data(global, input);
		if (global->input != NULL)
			execute_commands(global);
		free_global(global, 0);
	}
}
