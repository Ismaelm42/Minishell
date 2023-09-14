/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:30 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:52:48 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		quoted_lexer_counter(int *counter, char **s);
static void		redirection_lexer_counter(int *counter, char **s);
static void		words_counter(int *counter, char **s);

static void	quoted_lexer_counter(int *counter, char **s)
{
	char	c;

	while (1)
	{
		if (**s == '\'' || **s == '\"')
		{
			c = **s;
			(*s)++;
			while (**s != c && **s != '\0')
				(*s)++;
			if (**s == c)
			{
				c = 0;
				(*s)++;
			}
		}
		while (**s != '\'' && **s != '\"' && **s != '|'
			&& **s != '<' && **s != '>' && **s != ' '
			&& **s != '\t' && **s != '\0')
			(*s)++;
		if (**s != '\'' && **s != '\"')
			break ;
	}
	*counter += 1;
}

static void	redirection_lexer_counter(int *counter, char **s)
{
	if (**s == '|')
		while (**s == '|')
			(*s)++;
	else
		while (**s == '<' || **s == '>')
			(*s)++;
	*counter += 1;
}

static void	words_counter(int *counter, char **s)
{
	if (**s != '\0')
	{
		if (**s != ' ' && **s != '\t'
			&& ((*s)[1] == ' ' || (*s)[1] == '\t'
			|| (*s)[1] == '<' || (*s)[1] == '>'
			|| (*s)[1] == '|' || (*s)[1] == '\0' ))
			*counter += 1;
		(*s)++;
	}
}

int	lexer_counter(char *s)
{
	int		counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
			quoted_lexer_counter(&counter, &s);
		else if (*s == '<' || *s == '>' || *s == '|')
			redirection_lexer_counter(&counter, &s);
		else
			words_counter(&counter, &s);
	}
	return (counter);
}
