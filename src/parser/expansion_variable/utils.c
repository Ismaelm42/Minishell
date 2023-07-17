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
void	read_from_history(int n, t_tokens *tokens, char *needle, int size)
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
			if (tokens[n].expanded)
				free(tokens[n].expanded);
			tokens[n].expanded = ft_substr(haystack, size, 10000, 0);
			tokens[n].expanded = ft_strtrim(tokens[n].expanded, "\n", 1);
			if (tokens[n].expanded[0] == '\"')
				tokens[n].expanded = ft_strtrim(tokens[n].expanded, "\"", 1);
			else
				tokens[n].expanded = ft_strtrim(tokens[n].expanded, "\'", 1);
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
t_tokens	*free_expansion_tokens(int n, t_tokens *tokens, int flag)
{
	int	i;

	if (flag == 0)
	{
		while (n > 0)
			free (tokens[--n].variable);
	}
	if (flag == 1)
	{
		i = 0;
		while (i < n)
		{
			free (tokens[i].variable);
			free (tokens[i].expanded);
			i++;
		}
	}
	free (tokens);
	return (NULL);
}

/*
Se encarga de escribir el nuevo input modificado con los valores de las variables de expansión.
*/
void	replace_function(char *new_input, char *input, t_tokens *tokens)
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
		if (i == tokens[j].position)
		{
			n = 0;
			while (tokens[j].expanded[n] != 0)
				new_input[k++] = tokens[j].expanded[n++];
			i += ft_strlen(tokens[j++].variable);
		}
		else
			new_input[k++] = input[i++];
	}
}
