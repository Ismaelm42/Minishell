#include "../../../include/minishell.h"


/*
Esta función se encarga de gestionar las comillas simples y dobles.
*/
void	quoted_token_splitter(int *n, char **s, char ***tokens)
{
	char	c;
	int		length;

	length = 0;
	c = **s;
	while ((*s)[length + 1] != c)
		length++;
	length += 2;
	(*tokens)[*n] = ft_substr(*s, 0, length);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

/*
Aquí se separará cualquiera de estos metacaracteres: |, <, <<, >, >>.
*/
void	redirection_token_splitter(int *n, char **s, char ***tokens)
{
	int	length;

	if (**s == '|')
	{
		(*tokens)[*n] = ft_substr(*s, 0, 1);
		(*s)++;
		*n += 1;
	}
	else
	{
		length = 0;
		while ((*s)[length] == '<' || (*s)[length] == '>')
			length++;
		(*tokens)[*n] = ft_substr(*s, 0, length);
		*n += 1;
		while (length -- > 0)
			(*s)++;
	}
}

/*
Gestiona todo los demás argumentos pasados a través del input mientras
no coincida ningún caracter con los caracteres especiales.
*/
void	words_splitter(int *n, char **s, char ***tokens)
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
		(*tokens)[*n] = ft_substr(*s, 0, length);
		*n += 1;
		while (length -- > 0)
		(*s)++;
	}
}

/*
Libera la memoria reservada en caso de fallo.
*/
char	**free_tokens(int n, char **tokens)
{
	while (n > 0)
		free (tokens[--n]);
	free (tokens);
	return (NULL);
}

/*
Se encarga de dividir en varios strings los argumentos pasados por terminal.
*/
char	**token_maker(char *s)
{
	char	**tokens;
	int		size;
	int		n;

	n = 0;
	size = token_counter(s);
	tokens = (char **)malloc(sizeof(char **) * size + 1);
	if (!tokens)
		return (NULL);
	while (n < size)
	{
		if (*s == '\'' || *s == '"')
			quoted_token_splitter(&n, &s, &tokens);
		else if (*s == '<' || *s == '>' || *s == '|')
			redirection_token_splitter(&n, &s, &tokens);
		else
			words_splitter(&n, &s, &tokens);
		if (!tokens[n - 1])
			return (free_tokens(n - 1, tokens));
	}
	tokens[n] = 0;
	return (tokens);
}

// int	main(void)
// {
// 	char	**str;
// 	char	*phrase = "         ls|kaka<huhuh|  jiji  koko  << zzz    ";
// 	int		i;

// 	str = token_maker(phrase);
// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		printf("str[%d] = %s\n", i, str[i]);
// 		i++;
// 	}
// 	printf("str[%d] = %s\n", i, str[i]);
// }
