#include "../../../include/minishell.h"

/*
Iniciar aquí en esta función la lista de Javi para el historial de las variables de
entorno y el de las variables locales.
*/
t_global	*init_struct(void)
{
	t_global	*global;

	global = (t_global *)calloc(sizeof(t_global), 1);
	return (global);
}

void	get_struct_data(t_global *global, char *input)
{
	global->input = ft_strdup(input);
	global->tokens = get_tokens(input);
	if (global->tokens == NULL)
		free(global->input);
}
