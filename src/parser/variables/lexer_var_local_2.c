/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var_local_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:47:13 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:00:28 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		var_quoted_lexer_counter(int *counter, char **s);
static void		var_words_counter(int *counter, char **s);

static void	var_quoted_lexer_counter(int *counter, char **s)
{
	char	c;

	c = **s;
	(*s)++;
	while (**s != c && **s != '\0')
		(*s)++;
	if ((**s) == c)
	{
		(*s)++;
		*counter += 1;
	}
	else
		*counter = 0;
}

static void	var_words_counter(int *counter, char **s)
{
	if (**s != '\0')
	{
		if (**s != ' ' && ((*s)[1] == '\''
			|| (*s)[1] == '"' || (*s)[1] == '\0' ))
			*counter += 1;
		(*s)++;
	}
}

void	var_quoted_lexer_splitter(int *n, char **s, char ***lexer)
{
	char	c;
	int		length;

	length = 0;
	c = **s;
	while ((*s)[length + 1] != c && (*s)[length + 1] != c)
		length++;
	length += 2;
	(*lexer)[*n] = ft_substr(*s, 0, length, 0);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

int	var_lexer_counter(char *s)
{
	int		counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
			var_quoted_lexer_counter(&counter, &s);
		else if (*s == ' ' || *s == '<' || *s == '>' || *s == '|' || *s == '!')
			return (counter = 0);
		else
			var_words_counter(&counter, &s);
	}
	return (counter);
}

void	var_words_splitter(int *n, char **s, char ***lexer)
{
	int	length;

	length = 0;
	while ((*s)[length] != '\'' && (*s)[length] != '"' && (*s)[length] != '\0')
		length++;
	if (length > 0)
	{
		(*lexer)[*n] = ft_substr(*s, 0, length, 0);
		*n += 1;
		while (length -- > 0)
			(*s)++;
	}
}
