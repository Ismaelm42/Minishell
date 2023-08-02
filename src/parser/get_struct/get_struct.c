#include "../../../include/minishell.h"

/*
Inicio de la estructura al principio del programa.
*/
t_global	*init_struct(char **env)
{
	t_global	*global;
	t_node		*lst_env;

	(void)env;
	lst_env = init_list();
	copy_environment(&lst_env, env);
	global = (t_global *)ft_calloc(sizeof(t_global), 1);
	global->lst_env = lst_env;
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
	if (global->input != NULL)
		input = ft_strjoin(global->input, input, 3);
	global->input = ft_strdup(input);
	printf("global->input = %s\n", global->input);
	if (get_tokens(input, global) != -2)
	{
		free(global->input);
		global->input = NULL;
	}
	free_global(global, 0);
}

