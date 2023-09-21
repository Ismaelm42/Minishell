/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:15 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/21 12:32:06 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	get_variable_from_env(int n, t_lexer *lexer, t_global *global);
static int	get_variable_from_local_var(int n, t_lexer *lexer, t_global *g);
static void	get_expansion_value(int n, t_lexer *lexer, t_global *global);

static int	get_variable_from_env(int n, t_lexer *lexer, t_global *global)
{
	char	*copy;
	char	*environment;

	copy = ft_substr(lexer[n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	environment = search_env_expand(copy, global->env);
	free_mem((void **)&copy);
	if (environment == NULL)
		return (1);
	lexer[n].expanded = ft_strdup(environment);
	free_mem((void **)&environment);
	return (0);
}

static int	get_variable_from_local_var(int n, t_lexer *lexer, t_global *global)
{
	char	*copy;
	char	*var;

	copy = ft_substr(lexer[n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	var = search_key(global->lst_local, copy);
	free_mem((void **)&copy);
	if (var == NULL)
		return (1);
	lexer[n].expanded = ft_strdup(var);
	return (0);
}

static void	get_expansion_value(int n, t_lexer *lexer, t_global *global)
{
	char	*lex;

	lex = lexer[n].variable;
	if (ft_strlen(lex) == 1)
		lexer[n].expanded = ft_strdup("'$'");
	else if (ft_strncmp(lex, "$?", ft_strlen(lex)) == 0)
		lexer[n].expanded = ft_itoa(global->exit_status);
	else if (ft_strncmp(lex, "$$", ft_strlen(lex)) == 0)
	{
		lexer[n].expanded = get_pid_process(global);
		if (lexer[n].expanded == NULL)
			lexer[n].expanded = ft_strdup("");
	}
	else if (get_variable_from_env(n, lexer, global) == 1)
		if (get_variable_from_local_var(n, lexer, global) == 1)
			lexer[n].expanded = ft_strdup("");
}

char	*expansion_variable(char *input, t_global *global)
{
	t_lexer		*lexer;
	char		*new_input;
	int			size;
	int			i;

	if (variable_expansion_counter(input) != 0)
	{
		lexer = get_variable_expansion_lexer(input);
		size = variable_expansion_counter(input);
		i = 0;
		while (i < size)
		{
			get_expansion_value(i, lexer, global);
			i++;
		}
		new_input = replace_variables(input, lexer);
		free_expansion_lexer(lexer, 1);
		if (variable_expansion_counter(new_input) != 0)
			new_input = expansion_variable(new_input, global);
		return (new_input);
	}
	else
		return (input);
}
