#include "../../../include/minishell.h"

/*
Función que permite conseguir la posición exacta en el input de todas las variables $.
tokens_ptr es un puntero a input que permite avanzar el puntero para que, si tenemos
dos veces la misma variable ($$ $$, por ejemplo), podamos conseguir la posición de
la segunda variable y la función ft_strnstr no devuelva de nuevo la anterior a esta.
*/
void	get_size_variables(int *variable, int *expanded, char *input, t_tokens *tokens)
{
	char	*tokens_ptr;
	int		n;
	int		i;

	tokens_ptr = input;
	*variable = 0;
	*expanded = 0;
	i = 0;
	while (tokens[i].variable != NULL)
	{
		*variable += ft_strlen(tokens[i].variable);
		*expanded += ft_strlen(tokens[i].expanded);
		tokens_ptr = ft_strnstr(tokens_ptr, tokens[i].variable, 1000);
		tokens[i].position = tokens_ptr - input;
		n = 0;
		while (tokens_ptr && n < ft_strlen(tokens[i].variable))
		{
			tokens_ptr++;
			n++;
		}
		i++;
	}
}

/*
Se encarga de realizar la sustitución del input que obtenemos por la terminal
a la versión final en la cual sustituimos todas las variables $ por su valor.
*/
char	*replace_variables(char *input, t_tokens *tokens)
{
	char	*new_input;
	int		input_size;
	int		var_size;
	int		exp_size;
	int		size;

	input_size = ft_strlen(input);
	get_size_variables(&var_size, &exp_size, input, tokens);
	size = (input_size - var_size + exp_size);
	new_input = (char *)calloc(sizeof(char), size + 1);
	replace_function(new_input, input, tokens);
	return (new_input);
}
