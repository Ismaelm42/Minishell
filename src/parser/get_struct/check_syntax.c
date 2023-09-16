/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:58 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:56:06 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int		quotes_check(char *lexer);
static int		pipes_and_redirections_check(char **lexer, int n);
static int		next_lexer_check(char **lexer, int n);

static int	quotes_check(char *lexer)
{
	char	c;
	int		i;

	c = 0;
	i = 0;
	while (lexer[i] != '\0')
	{
		while (lexer[i] != '\'' && lexer[i] != '\"' && lexer[i] != '\0')
			i++;
		if (lexer[i] == '\'' || lexer[i] == '\"')
		{
			c = lexer[i++];
			while (lexer[i] != c && lexer[i] != '\0')
				i++;
			if (lexer[i] == c)
			{
				c = 0;
				i++;
			}
		}
	}
	if (c != 0)
		return (ft_putstr_fd("minishell: Syntax error unexpected EOF\n", 2), 2);
	return (0);
}

static int	pipes_and_redirections_check(char **lexer, int n)
{
	if ((lexer[n][0] == '|'
		&& (ft_strlen(lexer[n]) > 1 || n == 0
			|| (lexer[n + 1] != NULL && lexer[n + 1][0] == '|')))
		|| (lexer[n][0] == '<' && (lexer[n][1] != '<' && lexer[n][1] != '\0'))
		|| (lexer[n][0] == '>' && (lexer[n][1] != '>' && lexer[n][1] != '\0'))
		|| ((lexer[n][0] == '>' || lexer[n][0] == '<')
		&& ft_strlen(lexer[n]) > 2))
	{
		ft_putstr_fd("minishell: Syntax error near unexpected token ", 2);
		ft_putstr_fd("\'", 2);
		ft_putchar_fd(lexer[n][0], 2);
		ft_putstr_fd("\'\n", 2);
		return (2);
	}
	return (0);
}

static int	next_lexer_check(char **lexer, int n)
{
	if (lexer[n][0] == '|' && lexer[n + 1] == NULL)
		return (-1);
	if ((lexer[n][0] == '<' || lexer[n][0] == '>')
		&& (lexer[n + 1] == NULL || lexer[n + 1][0] == '|'
		|| lexer[n + 1][0] == '<' || lexer[n + 1][0] == '>'))
	{
		ft_putstr_fd("minishell: Syntax error near unexpected token ", 2);
		ft_putstr_fd("\'", 2);
		ft_putchar_fd(lexer[n][0], 2);
		if (lexer[n][1] != '\0')
			ft_putchar_fd(lexer[n][1], 2);
		ft_putstr_fd("\'\n", 2);
		return (2);
	}
	return (0);
}

int	syntax_error_check(char **lexer)
{
	int	n;
	int	ret;

	n = 0;
	ret = 0;
	while (lexer[n] != NULL)
	{
		ret = quotes_check(lexer[n]);
		if (ret == 0)
			ret = pipes_and_redirections_check(lexer, n);
		if (ret == 0)
			ret = next_lexer_check(lexer, n);
		if (ret != 0)
			return (ret);
		n++;
	}
	return (0);
}
