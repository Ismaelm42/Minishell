#include "../../../include/minishell.h"

/*
Creación de la estructura en la cual se reenvía a cada campo lexer->input
del array el puntero input para poder tener acceso a éste y poder
calcular la posición de cada variable de expansión.
*/

t_lexer	*create_expansion_lexer_struct(char *input, int size)
{
	t_lexer	*lexer;
	int		i;

	lexer = (t_lexer *)ft_calloc(sizeof(t_lexer), size + 1);
	i = 0;
	while (i < size)
	{
		lexer[i].input = input;
		i++;
	}
	return (lexer);
}
/*
Toma en cuenta los casos complicados con la variable de expansión.
Si hay un espacio tras esta no se considera variable de expansión sino
como un signo literal. Si se encuentra otro $ lo cuenta como uno y
si encuentra unos corchetes abiertos lo protege y lo toma como variable.
*/
void	handle_edge_cases(char **input, int *counter)
{
	if ((*input)[1] == '\'' || (*input)[1] == '"'
			|| (*input)[1] == '<' || (*input)[1] == '>'
			|| (*input)[1] == ' ' || (*input)[1] == '\t'
			|| (*input)[1] == '|' || (*input)[1] == '\0')
	{
		(*input)++;
		return ;
	}
	if ((*input)[1] == '$')
		(*input)++;
	else if ((*input)[1] == '{')
		while (**input != '}' && **input != '\0')
			(*input)++;
	*counter += 1;
}

/*
Permite avanzar el puntero cuando se encuentre unas comillas simples
y establece un lock cuando la comilla es doble de forma que pueda
realizar las expansiones.
*/
void	skip_quotes(char **s, int *lock)
{
	if (**s == '\'' && *lock == 0)
	{
		(*s)++;
		while (**s != '\'' && **s != '\0')
			(*s)++;
	}
	else if (**s == '\"')
	{
		if (*lock == 0)
			*lock = 1;
		else
			*lock = 0;
	}
	(*s)++;
}

int	check_edge_cases(char *s)
{
	if (*s == '$' && s[1] != '\''
		&& s[1] != '"' && s[1] != '<'
		&& s[1] != '>' && s[1] != ' '
		&& s[1] != '\t' && s[1] != '|'
		&& s[1] != '\0')
		return (0);
	else
		return (1);
}

/*
¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡FUNCION OBSOLETA!!!!!!!!!!!!!!!!!!!
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
Función para liberar la memoria. La liberación se realiza dependiendo del flag.
Si el flag es 1, eso quiere decir que la estructura también tiene completado el campo
lexer->expanded.
*/
t_lexer	*free_expansion_lexer(t_lexer *lexer, int flag)
{
	int	i;

	i = 0;
	while (lexer[i].variable != NULL)
	{
		free (lexer[i].variable);
		if (flag == 1)
			free (lexer[i].expanded);
		i++;
	}
	free (lexer);
	return (NULL);
}
