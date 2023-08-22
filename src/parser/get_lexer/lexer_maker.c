#include "../../../include/minishell.h"

char	*delete_quotes_substr(char *s)
{
	char	*substr;
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = 0;
	substr = (char *) malloc(sizeof(char) * ft_strlen(s));
	while (s[j] != '\0')
	{
		if (c != 0 && c == s[j])
		{
			c = 0;
			j++;
		}
		if (c == 0 && (s[j] == '\'' || s[j] == '\"'))
			c = s[j++];
		substr[i++] = s[j++];
	}
	substr[i] = '\0';
	if (c != 0)
		return (free(substr), s);
	return (free(s), substr);
}

/*
Aquí se separará cualquiera de estos metacaracteres: |, <, <<, >, >>.
*/
void	redirection_lexer_splitter(int *n, char **s, char ***lexer)
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

/*
Gestiona todo los demás argumentos pasados a través del input mientras
no coincida ningún caracter con los caracteres especiales.
*/
void	words_splitter(int *n, char **s, char ***lexer)
{
	char	c;
	int		length;

	length = 0;
	while (1)
	{
		while ((*s)[length] != '\0' && (*s)[length] != ' '
			&& (*s)[length] != '\t' && (*s)[length] != '|'
			&& (*s)[length] != '\'' && (*s)[length] != '\"'
			&& (*s)[length] != '<' && (*s)[length] != '>')
			length++;
		c = 0;
		if ((*s)[length] == '\'' || (*s)[length] == '\"')
		{
			c = (*s)[length++];
			while ((*s)[length] != c && (*s)[length] != '\0')
				length++;
			length++;
		}
		if ((*s)[length] == '\0' || (*s)[length] == ' '
			|| (*s)[length] == '\t' || (*s)[length] == '|'
			|| (*s)[length] == '<' || (*s)[length] == '>')
			break ;
	}
	(*lexer)[*n] = delete_quotes_substr(ft_substr(*s, 0, length, 0));
	*n += 1;
	while (length -- > 0)
	(*s)++;
}

/*
Se encarga de dividir en varios strings los argumentos pasados por terminal.
*/
char	**lexer_maker(char *s)
{
	char	**lexer;
	int		size;
	int		n;

	n = 0;
	size = lexer_counter(s);
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
			return (free_matrix(lexer));
	}
	lexer[n] = 0;
	return (lexer);
}
