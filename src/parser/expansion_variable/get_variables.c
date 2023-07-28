#include "../../../include/minishell.h"

/*
Función para contar el número de símbolos $ que hay que tener en cuenta.
Contempla todos los casos problemáticos por ahora.
*/

void	handle_edge_cases(char **input, int *counter)
{
	if ((*input)[1] == '$')
		(*input)++;
	else if ((*input)[1] == '{')
		while (**input != '}' && **input != '\0')
			(*input)++;
	*counter += 1;
}

int	variable_expansion_counter(char *input)
{
	int		counter;
	char	c;

	counter = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '\"')
		{
			c = *input;
			input++;
			while (*input != c && *input != '\0')
			{
				if (*input == '$' && c == '\"')
					handle_edge_cases(&input, &counter);
				input++;
			}
		}
		else if (*input == '$')
			handle_edge_cases(&input, &counter);
		input++;
	}
	return (counter);
}

/*
Permite avanzar el puntero cuando se encuentre unas comillas simples.
*/
void	skip_quotes_and_check_expansion(int *n, char **s, t_lexer *lexer)
{
	char	c;

	c = **s;
	(*s)++;
	while (**s != c && **s != '\0')
	{
		if (**s == '$' && c == '\"')
			check_expansion_and_delimiters(n, s, lexer);
		else
			(*s)++;
	}
	if (**s != '\0')
		(*s)++;
}

/*
Utiliza substring para crear la subcadena correspondiente, avanza el puntero de s
y suma uno más a n.
*/
void	variable_lexer_filler(int *n, int length, char **s, t_lexer *lexer)
{
	lexer[*n].variable = ft_substr(*s, 0, length, 0);
	lexer[*n].position = ft_strlen(lexer[*n].input) - ft_strlen(*s);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

/*
Permite guardar como lexer todos los símbolos $ teniendo en cuenta
los casos particulares como $, $123, $$, $?, $$$ARG, etc...
*/
void	check_expansion_and_delimiters(int *n, char **s, t_lexer *lexer)
{
	int	length;

	length = 1;
	if (((*s)[length] >= '0' && (*s)[length] <= '9')
		|| (*s)[length] == '?' || (*s)[length] == '$')
		length++;
	else if ((*s)[length] == '{')
	{
		while ((*s)[length] != '}' && (*s)[length] != '\0')
			length++;
		length++;
	}
	else
	{
		while ((*s)[length] != '\'' && (*s)[length] != '"'
			&& (*s)[length] != '<' && (*s)[length] != '>'
			&& (*s)[length] != ' ' && (*s)[length] != '\t'
			&& (*s)[length] != '|' && (*s)[length] != '\0')
		{
			if (length > 1 && (*s)[length] == '$')
				break ;
			length++;
		}
	}
	variable_lexer_filler(n, length, s, lexer);
}

/*
Guarda en un struct todos los posibles símbolos $ para sustituirlos en
el char *input antes de pasar por el lexer_counter/lexer_maker, de forma
que si esa variable tiene a su vez metacaracteres, éstos puedan ser
interpretados.
Casos tenidos en cuenta: $$, $?, $$$ARG, $012345, $ARG, $ARG|<<<>>>...
En principio cubre todos los casos existentes.
*/
t_lexer	*get_variable_expansion_lexer(char *input)
{
	t_lexer		*lexer;
	int			size;
	int			n;

	size = variable_expansion_counter(input);
	lexer = create_expansion_lexer_struct(input, size);
	n = 0;
	while (n < size)
	{
		if (*input == '\'' || *input == '\"' || *input == '$')
		{
			if (*input != '$')
				skip_quotes_and_check_expansion(&n, &input, lexer);
			else
				check_expansion_and_delimiters(&n, &input, lexer);
			if (!lexer[n - 1].variable)
				return (free_expansion_lexer(lexer, 0));
		}
		else
			input++;
	}
	lexer[n].variable = 0;
	return (lexer);
}
