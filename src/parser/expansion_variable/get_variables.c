#include "../../../include/minishell.h"

/*
Función para contar el número de símbolos $ que hay que tener en cuenta.
Contempla todos los casos problemáticos por ahora.
*/
int	variable_expansion_counter(char *input)
{
	int	counter;

	counter = 0;
	while (*input != '\0')
	{
		if (*input == '\'')
		{
			input++;
			while (*input != '\'')
				input++;
		}
		else if (*input == '$')
		{
			if (input[1] == '$')
				input++;
			else if (input[1] == '{')
				while (*input != '}' && *input != '\0')
					input++;
			counter++;
		}
		input++;
	}
	return (counter);
}

/*
Permite avanzar el puntero cuando se encuentre unas comillas simples.
*/
void	skip_quotes(char **s)
{
	(*s)++;
	while (**s != '\'' && **s != '\0')
		(*s)++;
	(*s)++;

}

/*
Permite guardar como token todos los símbolos $ teniendo en cuenta
los casos particulares como $, $123, $$, $?, $$$ARG, etc...
*/
void	tokens_filler(int *n, char **s, t_tokens *tokens)
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
	tokens[*n].variable = ft_substr(*s, 0, length);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}
/*
Función para liberar la memoria. Se resta primero para bajar un nivel más
ya que en n es donde ha fallado la memoria.
*/
t_tokens	*free_expansion_tokens(int n, t_tokens *tokens, int flag)
{
	while (n > 0)
	{
		n--;
		free (tokens[n].variable);
		if (flag != 0)
			free (tokens[n].variable);
	}
	free (tokens);
	return (NULL);
}

/*
Guarda en un struct todos los posibles símbolos $ para sustituirlos en
el char *input antes de pasar por el token_counter/token_maker, de forma
que si esa variable tiene a su vez metacaracteres, éstos puedan ser
interpretados.
Casos tenidos en cuenta: $$, $?, $$$ARG, $012345, $ARG, $ARG|<<<>>>...
En principio cubre todos los casos existentes.
*/
t_tokens	*variable_expansion_tokens(char *input)
{
	t_tokens	*tokens;
	int			size;
	int			n;

	size = variable_expansion_counter(input);
	tokens = (t_tokens *)ft_calloc(sizeof(t_tokens), size + 1);
	if (!tokens)
		return (NULL);
	n = 0;
	while (n < size)
	{
		if (*input == '\'')
			skip_quotes(&input);
		else if (*input == '$')
		{
			tokens_filler(&n, &input, tokens);
			if (!tokens[n - 1].variable)
				return (free_expansion_tokens(n - 1, tokens, 0));
		}
		else
			input++;
	}
	tokens[n].variable = 0;
	return (tokens);
}

int	main(void)
{
	t_tokens	*prueba;
	char	*str = "    ${ARG$hola$?";

	printf("%d\n", variable_expansion_counter(str));
	prueba = variable_expansion_tokens(str);

	int i = 0;
	while (prueba[i].variable != NULL)
	{
		printf("prueba[%d] = %s\n", i, prueba[i].variable);
		i++;
	}
	printf("prueba[%d] = %s\n", i, prueba[i].variable);

	return (0);
}
