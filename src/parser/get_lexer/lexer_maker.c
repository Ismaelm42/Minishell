#include "../../../include/minishell.h"


/*
Esta función se encarga de gestionar las comillas simples y dobles.
*/
void	quoted_lexer_splitter(int *n, char **s, char ***lexer)
{
	char	c;
	int		length;

	length = 0;
	c = **s;
	while ((*s)[length + 1] != c)
		length++;
	length += 2;
	(*lexer)[*n] = ft_substr(*s, 0, length, 0);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

/*
Aquí se separará cualquiera de estos metacaracteres: |, <, <<, >, >>.
*/
void	redirection_lexer_splitter(int *n, char **s, char ***lexer)
{
	int	length;

	if (**s == '|')
	{
		(*lexer)[*n] = ft_substr(*s, 0, 1, 0);
		(*s)++;
		*n += 1;
	}
	else
	{
		length = 0;
		while ((*s)[length] == '<' || (*s)[length] == '>')
			length++;
		(*lexer)[*n] = ft_substr(*s, 0, length, 0);
		*n += 1;
		while (length -- > 0)
			(*s)++;
	}
}

/*
Gestiona todo los demás argumentos pasados a través del input mientras
no coincida ningún caracter con los caracteres especiales.
*/
void	words_splitter(int *n, char **s, char ***lexer)
{
	int	length;

	length = 0;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	while ((*s)[length] != '\'' && (*s)[length] != '"'
		&& (*s)[length] != '<' && (*s)[length] != '>'
		&& (*s)[length] != ' ' && (*s)[length] != '\t'
		&& (*s)[length] != '|' && (*s)[length] != '\0')
		length++;
	if (length > 0)
	{
		(*lexer)[*n] = ft_substr(*s, 0, length, 0);
		*n += 1;
		while (length -- > 0)
		(*s)++;
	}
}

/*
Libera la memoria reservada en caso de fallo.
*/
char	**free_lexer(int n, char **lexer)
{
	while (n > 0)
		free (lexer[--n]);
	free (lexer);
	return (NULL);
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
	lexer = (char **)calloc(sizeof(char **), size + 1);
	while (n < size)
	{
		if (*s == '\'' || *s == '"')
			quoted_lexer_splitter(&n, &s, &lexer);
		else if (*s == '<' || *s == '>' || *s == '|')
			redirection_lexer_splitter(&n, &s, &lexer);
		else
			words_splitter(&n, &s, &lexer);
		if (!lexer[n - 1])
			return (free_lexer(n - 1, lexer));
	}
	lexer[n] = 0;
	return (lexer);
}
