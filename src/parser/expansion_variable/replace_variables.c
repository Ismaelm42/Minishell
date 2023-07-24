#include "../../../include/minishell.h"

/*
Función que permite conseguir la posición exacta en el input de todas las variables $.
lexer_ptr es un puntero a input que permite avanzar el puntero para que, si tenemos
dos veces la misma variable ($$ $$, por ejemplo), podamos conseguir la posición de
la segunda variable y la función ft_strnstr no devuelva de nuevo la anterior a esta.
*/
void	get_size_variables(int *variable, int *expanded, char *input, t_lexer *lexer)
{
	char	*lexer_ptr;
	int		n;
	int		i;

	lexer_ptr = input;
	*variable = 0;
	*expanded = 0;
	i = 0;
	while (lexer[i].variable != NULL)
	{
		*variable += ft_strlen(lexer[i].variable);
		*expanded += ft_strlen(lexer[i].expanded);
		lexer_ptr = ft_strnstr(lexer_ptr, lexer[i].variable, 1000);
		lexer[i].position = lexer_ptr - input;
		n = 0;
		while (lexer_ptr && n < ft_strlen(lexer[i].variable))
		{
			lexer_ptr++;
			n++;
		}
		i++;
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
	get_size_variables(&var_size, &exp_size, input, lexer);
	size = (input_size - var_size + exp_size);
	new_input = (char *)calloc(sizeof(char), size + 1);
	replace_function(new_input, input, lexer);
	return (new_input);
}
