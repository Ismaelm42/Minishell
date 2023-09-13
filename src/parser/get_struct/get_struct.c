#include "../../../include/minishell.h"

extern int g_status;

/*
Inicio de la estructura al principio del programa.
*/
t_global	*init_struct(char **env)
{
	t_global	*global;

	global = (t_global *)ft_calloc(sizeof(t_global), 1);
	global->env = copy_environment(env);
	global->lst_env = init_list();
	global->exit_status = 0;
	global->pid = NULL;
	global->fd = NULL;
	tcgetattr(STDIN_FILENO, &global->prompt);
	copy_environment_list(&global->lst_env, env);
	ft_envlst_short(&global->lst_env);
	return (global);
}

/*
Función que recoge todo el procedimiento del parseo.
Con esta función se generará la estructura apropiada para cada input
y se liberará con la función free global y el parámetro 0 toda la información
que ya no es necesaria (tokens) para seguir con una nueva linea.
*/

void	get_struct_data(t_global *global, char *input)
{
	int	token_return;

	signal(SIGINT, ft_sigint_open_pipe);
	global->input = ft_strdup(input);
	token_return = -1;
	while (token_return == -1)
	{
		//global->exit_status = 0; entra siempre No nos vale
		token_return = get_tokens(input, global);
		if (token_return != -1)
			break ;
		input = readline("> ");
		dprintf(2, "GLOBAL STATUS = %d\n", global->exit_status);
		if (!input || global->exit_status == 1) 
			break ;
		input = ft_strjoin(global->input, input, 3);
		global->input = ft_strdup(input);
	}
	if (token_return != 0)
		free_global(global, 0);
}
