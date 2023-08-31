#include "../../../include/minishell.h"

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

// Función quee cuenta string entre comillados si estas no estan cerradas
//  pondra contador a 0 y mostrara error

void	var_quoted_lexer_counter(int *counter, char **s)
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

// Función quee cuenta string sin comillas si contiene caracteres
// no válidos pondrá contador a 0 y mostrar error

void	var_words_counter(int *counter, char **s)
{
	if (**s != '\0')
	{
		if (**s != ' ' && ((*s)[1] == '\''
			|| (*s)[1] == '"' || (*s)[1] == '\0' ))
			*counter += 1;
		(*s)++;
	}
}

// Funcion que realiza el conteo de "subcadenas" para la reserva de memoria

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
