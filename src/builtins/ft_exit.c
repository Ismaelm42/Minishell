#include "../../include/minishell.h"

/*
-BASH-
exit 123 123 -> cierra con error en salida standar too many argumets ,exit status  1;
exit -> cierra con exit status 0;
******
exit 42 WORLD -> no cierra muestra un exit /n too many arguments, exit status 1
exit WOLD 42 -> cierra , exit status 1 (mirar en test si saca tb mnsaje too many arguments)
exit WORLD WORLD -> cierra 

RESUMIENDO no cierra solo si el primer argumento es numerico
*****
exit 123 -> ciera con exit status 123 ( va del 0 al 254 )
*/

static int	is_param_digit(t_global *g, int n, int j)
{
	int	i;

	i = 0;
	if (g->tokens[n].arg[j][i] == '+' || g->tokens[n].arg[j][i] == '-')
		i++;
	while (ft_isdigit(g->tokens[n].arg[j][i]) == 1
			&& g->tokens[n].arg[0][i] != '\0')
			i++;
	if (g->tokens[n].arg[j][i] == '\0')
		return (0);
	return (1);
}

void	ft_exit_more_params(t_global *g, int n)
{
	if (is_param_digit(g, n, 0) == 0)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		g->exit_status = 1;
	}
	else
	{
		free_global(g, 1);
		exit (1);
	}	
}


void	ft_exit(t_global *g, int n)
{
	int	arg;

	if (g->tokens[n].arg[0] != NULL && g->tokens[n].arg[1] != NULL)
		ft_exit_more_params(g, n);
	else if (g->tokens[n].arg[0] != NULL)
	{
		if (is_param_digit(g, n, 0) == 0)
		{
			arg = ft_atoi(g->tokens[n].arg[0]);
			free_global(g, 1);
			exit(arg);
		}
		else
		{
			ft_putstr_fd("minishell: numeric argument required\n", 2);
			free_global(g, 1);
			exit (255);
		}
	}
	else
	{
		free_global(g, 1);
		exit(0);
	}	
}
