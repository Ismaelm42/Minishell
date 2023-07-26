#include "../../../include/minishell.h"

/*
Iniciar aquí en esta función la lista de Javi para el historial de las variables de
entorno y el de las variables locales.
*/
t_global	*init_struct(char **env)
{
	t_global	*global;
	t_node		*lst_env;

	lst_env = init_list();
	copy_environment(&lst_env, env);
	global = (t_global *)ft_calloc(sizeof(t_global), 1);
	global->lst_env = lst_env;
	return (global);
}

void	get_struct_data(t_global *global, char *input)
{
	global->input = ft_strdup(input);
	global->tokens = get_tokens(input, global);
	if (global->tokens == NULL)
		free(global->input);
}
