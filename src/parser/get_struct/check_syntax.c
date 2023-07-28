#include "../../../include/minishell.h"

int	quotes_check(char **lexer, int n)
{
	if ((lexer[n][0] == '\'' && lexer[n][ft_strlen(lexer[n]) - 1] != '\'')
		|| (lexer[n][0] == '\"' && lexer[n][ft_strlen(lexer[n]) - 1] != '\"'))
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file", 2);
		free_lexer(lexer);
		return (-1);
	}
	return (0);
}

int	pipes_and_redirections_check(char **lexer, int n)
{
	if ((lexer[n][0] == '|' && (ft_strlen(lexer[n]) > 1 || n == 0))
		|| (lexer[n][0] == '<' && (lexer[n][1] != '<' && lexer[n][1] != '\0'))
		|| (lexer[n][0] == '>' && (lexer[n][1] != '>' && lexer[n][1] != '\0'))
		|| ((lexer[n][0] == '>' || lexer[n][0] == '<')
		&& ft_strlen(lexer[n]) > 2))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("\'", 2);
		ft_putchar_fd(lexer[n][0], 2);
		ft_putstr_fd("\'\n", 2);
		free_lexer(lexer);
		return (-1);
	}
	return (0);
}

int	next_lexer_check(char **lexer, int n)
{
	if ((lexer[n][0] == '|' || lexer[n][0] == '<'
		|| lexer[n][0] == '>') && (lexer[n + 1] == NULL // Solo contemplar los casos con varios pipes. Las redirecciones no deberían afectar en nada.
		|| lexer[n + 1][0] == '|' || lexer[n + 1][0] == '<'
		|| lexer[n + 1][0] == '>'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("\'", 2);
		ft_putchar_fd(lexer[n][0], 2);
		ft_putstr_fd("\'\n", 2);
		free_lexer(lexer);
		return (-1);
	}
	return (0);
}

int	syntax_error_check(char **lexer)
{
	int	n;

	n = 0;
	while (lexer[n] != NULL)
	{
		if (quotes_check(lexer, n) == -1
			|| pipes_and_redirections_check(lexer, n) == -1
			|| next_lexer_check(lexer, n) == -1)
			break ;
		n++;
	}
	if (lexer[n] != NULL)
		return (-1);
	return (0);
}
