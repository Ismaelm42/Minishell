/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:42 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:53:13 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		redirection_lexer_splitter(int *n, char **s, char ***lexer);
static void		words_splitter(int *n, char **s, char ***lexer);

static void	redirection_lexer_splitter(int *n, char **s, char ***lexer)
{
	int	length;

	length = 0;
	if (**s == '|')
		while ((*s)[length] == '|')
			length++;
	else
		while ((*s)[length] == '<' || (*s)[length] == '>')
			length++;
	(*lexer)[*n] = ft_substr(*s, 0, length, 0);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

static void	words_splitter(int *n, char **s, char ***lexer)
{
	int		length;

	length = 0;
	while (1)
	{
		while ((*s)[length] != '\0' && (*s)[length] != ' '
			&& (*s)[length] != '\t' && (*s)[length] != '|'
			&& (*s)[length] != '\'' && (*s)[length] != '\"'
			&& (*s)[length] != '<' && (*s)[length] != '>')
			length++;
		check_quotes(*s, &length);
		if ((*s)[length] == '\0' || (*s)[length] == ' '
			|| (*s)[length] == '\t' || (*s)[length] == '|'
			|| (*s)[length] == '<' || (*s)[length] == '>')
			break ;
	}
	(*lexer)[*n] = ft_substr(*s, 0, length, 0);
	*n += 1;
	while (length -- > 0)
	(*s)++;
}

char	**lexer_maker(char *s)
{
	char	**lexer;
	int		size;
	int		n;

	n = 0;
	size = lexer_counter(s);
	if (size == 0)
		return (NULL);
	lexer = (char **)ft_calloc(sizeof(char **), size + 1);
	while (n < size)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		if (*s == '<' || *s == '>' || *s == '|')
			redirection_lexer_splitter(&n, &s, &lexer);
		else
			words_splitter(&n, &s, &lexer);
		if (!lexer[n - 1])
			return (free_matrix((void ***)&lexer, 0));
	}
	lexer[n] = 0;
	return (lexer);
}
