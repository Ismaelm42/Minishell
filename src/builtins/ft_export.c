#include "../../include/minishell.h"

static int	parse_arg(t_global *g, int n, int i)
{
	char	*val;

	if (ft_strrchr(g->tokens[n].arg[i], '=') == NULL)
	{	
		if (check_key(g->tokens[n].arg[i], 0) != 0)
			return (1);
	}	
	else
	{
		if (check_key(extract_clue(g->tokens[n].arg[i]), 1) != 0)
			return (1);
		else
		{	
			val = extract_value(g->tokens[n].arg[i]);
			if (ft_strchr(val, '!' ) != NULL)
			{
				free_mem((void **)&val);
				return (1);
			}
			else
				free_mem((void **)&val);
		}
	}
	return (0);
}

void	action_export(t_global *g, int n, int i)
{
	char	*key;

	while ((g->tokens[n].arg[i] != NULL))
	{
		if (parse_arg(g, n, i) == 0)
		{
			if (ft_strrchr(g->tokens[n].arg[i], '=') == NULL)
			{
				if (search_key(g->lst_env, g->tokens[n].arg[i]) == NULL)
				{
					key = ft_strdup(g->tokens[n].arg[i]);
					insert_last(&g->lst_env, create_nodo(key, ft_strdup("")));
				}
			}
			else
			{
				if (search_key_and_replace(g->lst_env, extract_clue \
				(g->tokens[n].arg[i]), extract_value(g->tokens[n].arg[i])))
					insert_last(&g->lst_env, create_nodo(extract_clue \
					(g->tokens[n].arg[i]), extract_value(g->tokens[n].arg[i])));
				if (search_env_replace(extract_clue(g->tokens[n].arg[i]), \
				extract_value(g->tokens[n].arg[i]), g->env))
					add_env(&g->env, g->tokens[n].arg[i]);
			}
		}
		i++;
	}
	ft_envlst_short(&g->lst_env);
}

void	ft_export(t_global *g, int n)
{
	if (g->tokens[n].arg[0] == NULL)
		print_stack(g->lst_env);
}

