#include "../../../include/minishell.h"

// Funcion que rercibira la clave del input realizara  el contao para la reserva
// (en el conteo se analizara sintacticamente devolviendo 0 si algo no 
//es correcto)

char	**var_lexer_maker(char *s)
{
	char	**lexer;
	int		size;
	int		n;

	n = 0;
	size = var_lexer_counter(s);
	lexer = (char **)ft_calloc(sizeof(char **), size + 1);
	while (n < size)
	{
		if (*s == '\'' || *s == '"')
			var_quoted_lexer_splitter(&n, &s, &lexer);
		else
			var_words_splitter(&n, &s, &lexer);
		if (!lexer[n - 1])
			return (free_matrix(lexer));
	}
	lexer[n] = 0;
	return (lexer);
}