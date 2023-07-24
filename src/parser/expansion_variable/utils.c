#include "../../../include/minishell.h"

/*
Lee del historial y se usan las funciones strtrim para recortar las comillas dobles o simples,
las que primero encuentre. Se está reservando y liberando constantemente para ir buscando
por el historial.
¡¡¡¡Nota!!!!:
En el condicional if (fd == -1), hay que crear un exit específico en utils que cierre
correctamente el programa.
Tiene en cuenta casos especiales como: ARG="'hola'", ARG='"hola"'...
*/
void	read_from_history(int n, t_lexer *lexer, char *needle, int size)
{
	char	*haystack;
	int		fd;

	fd = open(".bash_history", 0666);
	if (fd == -1)
		ft_putstr_fd("Error openning bash history\n", 2);
	haystack = gnl(fd);
	while (haystack != NULL)
	{
		if (ft_strnstr(haystack, needle, ft_strlen(needle)))
		{
			if (lexer[n].expanded)
				free(lexer[n].expanded);
			lexer[n].expanded = ft_substr(haystack, size, 10000, 0);
			lexer[n].expanded = ft_strtrim(lexer[n].expanded, "\n", 1);
			if (lexer[n].expanded[0] == '\"')
				lexer[n].expanded = ft_strtrim(lexer[n].expanded, "\"", 1);
			else
				lexer[n].expanded = ft_strtrim(lexer[n].expanded, "\'", 1);
		}
		free(haystack);
		haystack = gnl(fd);
	}
	close(fd);
}

/*
Función para liberar la memoria. Se resta primero para bajar un nivel más
ya que en n es donde ha fallado la memoria.
*/
t_lexer	*free_expansion_lexer(int n, t_lexer *lexer, int flag)
{
	int	i;

	if (flag == 0)
	{
		while (n > 0)
			free (lexer[--n].variable);
	}
	if (flag == 1)
	{
		i = 0;
		while (i < n)
		{
			free (lexer[i].variable);
			free (lexer[i].expanded);
			i++;
		}
	}
	free (lexer);
	return (NULL);
}

/*
Se encarga de escribir el nuevo input modificado con los valores de las variables de expansión.
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
