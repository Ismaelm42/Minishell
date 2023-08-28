#include "../../include/minishell.h"

int	check_builtins(t_global *g, int n)
{
	//se debería checkear si command es igual a null y
	//basicamente que entre en get_commands y siga el curso normal. Comentando
	//check_builtins el comando >outfile funciona perfectamente.
	//Por lo tanto, el problema viene en principio de esta función.
	//Creo que simplemente deberías de hacer check en si el command es NULL.
	//Esta función está comentada en la función execute_commands y en su primera
	//aparición en child_process.
	if ((ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		|| (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
		|| (ft_strncmp(g->tokens[n].command, "unset", 6) == 0)
		|| (ft_strncmp(g->tokens[n].command, "echo", 5) == 0))
		return (0);
	else
		return (1);
}

void	builtins(t_global *g, int n)
{
	if (ft_strncmp(g->tokens[n].command, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(g->tokens[n].command, "env", 4) == 0)
		ft_env(g);
	else if (ft_strncmp(g->tokens[n].command, "export", 7) == 0)
		ft_export(g, n);
	else if (ft_strncmp(g->tokens[n].command, "unset", 6) == 0)
		ft_unset(g, n);
	else if (ft_strncmp(g->tokens[n].command, "echo", 5) == 0)
		ft_echo(g, n);
	free_global(g, 0);
	exit(1);
}
	