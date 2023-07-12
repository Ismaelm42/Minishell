#include "../../include/minishell.h"

typedef struct s_tokens
{
	char	*token;
	char	*expanded_token;
}			t_tokens;

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
void	tokens_filler(int *n, char **s, char ***tokens)
{
	int	length;

	length = 1;
	if ((*s)[length] >= '0' && (*s)[length] <= '9')
	{
		length++;
		(*tokens)[*n] = ft_substr(*s, 0, length);
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
		(*tokens)[*n] = ft_substr(*s, 0, length);
	}
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

/*
Guarda en un struct todos los posibles símbolos $ para sustituirlos en
el char *input antes de pasar por el token_counter/token_maker, de forma
que si esa variable tiene a su vez metacaracteres, éstos puedan ser
interpretados.
*/
char	**variable_expansion_tokens(char *input)
{
	char	**tokens;
	int		size;
	int		n;

	size = variable_expansion_counter(input);
	tokens = (char **)malloc(sizeof(char *) * size + 1);
	if (!tokens)
		return (NULL);
	n = 0;
	while (n < size)
	{
		if (*input == '\'')
			skip_quotes(&input);
		else if (*input == '$')
		{
			tokens_filler(&n, &input, &tokens);
			if (!tokens[n - 1])
				return (free_tokens(n - 1, tokens));
		}
		else
			input++;
	}
	tokens[n] = 0;
	return (tokens);
}

int	main(void)
{
	char	**prueba;
	char	*str = "898e9we";

	printf("%d\n", variable_expansion_counter(str));
	prueba = variable_expansion_tokens(str);

	int i = 0;
	while (prueba[i] != NULL)
	{
		printf("prueba[%d] = %s\n", i, prueba[i]);
		i++;
	}
	printf("prueba[%d] = %s\n", i, prueba[i]);
	return (0);
}

//El parseo aquí está hecho de tal modo que si encuentra $$$ARG
//Lo va a guardar en dos char* $$ y $ARG
//Pero si se encuentra con argumentos como $$234
//Lo va a guardar como una cadena entera y lo guardará en un char*
//Tal y como hace BASH


//gnl tiene que leer hasta el final para comprobar que la variable no se haya machacado.
//tener en cuenta varias variables $
//si encuentra una comilla lo avanza a full sino lo pilla del tirón
