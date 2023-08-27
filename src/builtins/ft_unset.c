#include "../../include/minishell.h"

/*
El comando unset eliminara una variable global o varias recibidas como
de argumento de char ** env 
y de lst_env. Puede recibir varias variables como Argumentos 
*/

void	ft_unset(t_global *g, int n)
{
	int	i;

	i = 0;
	if (!g->tokens[n].arg[0])
		exit (0);
	else
	{
		while (g->tokens[n].arg[i] != NULL)
		{
			search_key_and_delete(&g->lst_env, g->tokens[n].arg[i]);
			i++;
		}
		//print_stack(g->lst_env);	
	}
}
