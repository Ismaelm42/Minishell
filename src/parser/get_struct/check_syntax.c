#include "../../../include/minishell.h"

/*
Controla los errores de comillas no cerradas
*/
int	quotes_check(char *lexer)
{
	char	c;
	int		i;

	c = 0;
	i = 0;
	while (lexer[i] != '\0')
	{
		while (lexer[i] != '\'' && lexer[i] != '\"' && lexer[i] != '\0')
			i++;
		if (lexer[i] == '\'' || lexer[i])
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

/*
Controla que los lexer en los que hay pipes y redirecciones sean correctos.
Es decir que verifica que no haya más de dos redirecciones, por ejemplo, etc.
*/
int	pipes_and_redirections_check(char **lexer, int n)
{
	if ((lexer[n][0] == '|' && (ft_strlen(lexer[n]) > 1 || n == 0))
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

/*
Checkea los casos particulares cuando se encuentra por ejemplo un pipe al final del input
y cuando se encuentra una redirección seguida de un pipe.
*/
int	next_lexer_check(char **lexer, int n)
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
