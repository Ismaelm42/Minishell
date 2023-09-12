#include "../../../include/minishell.h"

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
	global->fd_stdin = dup(STDIN_FILENO);
	if (global->fd_stdin == -1)
		return (free_global(global, 1), NULL);
	global->fd_stdout = dup(STDOUT_FILENO);
	if (global->fd_stdout == -1)
		return (free_global(global, 1), NULL);
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

	global->input = ft_strdup(input);
	token_return = -1;
	while (token_return == -1)
	{
		token_return = get_tokens(input, global);
		if (token_return != -1)
			break ;
		input = readline("> ");
		input = ft_strjoin(global->input, input, 3);
		global->input = ft_strdup(input);
	}
	if (token_return != 0)
		free_global(global, 0);
}
