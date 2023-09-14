/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:05 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:45:06 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_lexer	*create_expansion_lexer_struct(char *input, int size)
{
	t_lexer	*lexer;
	int		i;

	lexer = (t_lexer *)ft_calloc(sizeof(t_lexer), size + 1);
	i = 0;
	while (i < size)
	{
		lexer[i].input = input;
		i++;
	}
	return (lexer);
}

void	handle_edge_cases(char **input, int *counter)
{
	if ((*input)[1] == '\0')
		return ;
	if ((*input)[1] == '\''
		|| (*input)[1] == '"' || (*input)[1] == '<'
		|| (*input)[1] == '>' || (*input)[1] == ' '
		|| (*input)[1] == '\t' || (*input)[1] == '|')
	{
		(*input)++;
		return ;
	}
	if ((*input)[1] == '$')
		(*input)++;
	else if ((*input)[1] == '{')
		while (**input != '}' && **input != '\0')
			(*input)++;
	*counter += 1;
}

void	skip_quotes(char **s, int *lock)
{
	if (**s == '\'' && *lock == 0)
	{
		(*s)++;
		while (**s != '\'' && **s != '\0')
			(*s)++;
	}
	else if (**s == '\"')
	{
		if (*lock == 0)
			*lock = 1;
		else
			*lock = 0;
	}
	(*s)++;
}

int	check_edge_cases(char *s)
{
	if (*s == '$' && s[1] != '\''
		&& s[1] != '"' && s[1] != '<'
		&& s[1] != '>' && s[1] != ' '
		&& s[1] != '\t' && s[1] != '|'
		&& s[1] != '\0')
		return (0);
	else
		return (1);
}

t_lexer	*free_expansion_lexer(t_lexer *lexer, int flag)
{
	int	n;

	n = 0;
	while (lexer[n].variable != NULL)
	{
		free (lexer[n].variable);
		if (flag == 1)
			free (lexer[n].expanded);
		n++;
	}
	free (lexer);
	return (NULL);
}
