#include "../../../include/minishell.h"

/*
Función que permite conseguir la posición exacta en el input de todas las variables $.
lexer_ptr es un puntero a input que permite avanzar el puntero para que, si tenemos
dos veces la misma variable ($$ $$, por ejemplo), podamos conseguir la posición de
la segunda variable y la función ft_strnstr no devuelva de nuevo la anterior a esta.
*/
void	get_size_variables(int *var, int *exp, t_lexer *lexer)
{
	int		i;

	i = 0;
	*var = 0;
	*exp = 0;
	while (lexer[i].variable != NULL)
	{
		*var += ft_strlen(lexer[i].variable);
		*exp += ft_strlen(lexer[i].expanded);
		i++;
	}
}

/*
Se encarga de escribir el nuevo input modificado con los valores de las variables
 de expansión.
*/
void	replace_function(char *new_input, char *input, t_lexer *lexer)
{
	int	i;
	int	j;
	int	k;
	int	n;

	i = 0;
	j = 0;
	k = 0;
	while (input[i] != 0)
	{
		if (i == lexer[j].position)
		{
			n = 0;
			while (lexer[j].expanded[n] != 0)
				new_input[k++] = lexer[j].expanded[n++];
			i += ft_strlen(lexer[j++].variable);
		}
		else
			new_input[k++] = input[i++];
	}
}

/*
Se encarga de realizar la sustitución del input que obtenemos por la terminal
a la versión final en la cual sustituimos todas las variables $ por su valor.
*/
char	*replace_variables(char *input, t_lexer *lexer)
{
	char	*new_input;
	int		input_size;
	int		var_size;
	int		exp_size;
	int		size;

	input_size = ft_strlen(input);
	get_size_variables(&var_size, &exp_size, lexer);
	size = (input_size - var_size + exp_size);
	new_input = (char *)ft_calloc(sizeof(char), size + 1);
	replace_function(new_input, input, lexer);
	free_mem((void **)&input);
	return (new_input);
}
