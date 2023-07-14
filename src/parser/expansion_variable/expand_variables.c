#include "../../../include/minishell.h"

/*
Obtiene la variable a través del Path. También controla en caso de que la variable
haya sido enviada entre paréntesis: ${HOME}
*/
int	get_variable_from_path(int *n, t_tokens *tokens)
{
	char	*copy;
	char	*environment;

	copy = ft_substr(tokens[*n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	environment = getenv(copy);
	if (environment == NULL)
		return (1);
	tokens[*n].expanded = ft_strdup(environment);
	free(copy);
	return (0);
}

/*
Lee del historial y se usan las funciones strtrim para recortar las comillas dobles o simples,
las que primero encuentre. Se está reservando y liberando constantemente para ir buscando
por el historial.
Nota:
En el condicional if (fd == -1), ay que crear un exit específico que cierre
correctamente el programa.
Tiene en cuenta casos especiales como: ARG="'hola'", ARG='"hola"'...
*/
void	read_from_history(int *n, t_tokens *tokens, char *needle, int size)
{
	char	*haystack;
	int		fd;

	fd = open(".bash_history", 0666);
	if (fd == -1)
		ft_putstr_fd("Error openning bash history", 2);
	haystack = gnl(fd);
	while (haystack != NULL)
	{
		if (ft_strnstr(haystack, needle, ft_strlen(needle)))
		{
			if (tokens[*n].expanded)
				free(tokens[*n].expanded);
			tokens[*n].expanded = ft_substr(haystack, size, 10000, 0);
			tokens[*n].expanded = ft_strtrim(tokens[*n].expanded, "\n", 1);
			if (tokens[*n].expanded[0] == '\"')
				tokens[*n].expanded = ft_strtrim(tokens[*n].expanded, "\"", 1);
			else
				tokens[*n].expanded = ft_strtrim(tokens[*n].expanded, "\'", 1);
		}
		free(haystack);
		haystack = gnl(fd);
	}
	close(fd);
}

/*
Crea needle que es nombre de la variable más el símbolo igual para poder
buscarlo por el historial en la función read_from_history.
Ejemplo de needle: ARG= 
*/
int	get_variable_from_history(int *n, t_tokens *tokens)
{
	char	*needle;
	int		size;

	size = ft_strlen(tokens[*n].variable);
	needle = ft_substr(tokens[*n].variable, 1, size, 0);
	needle = ft_strjoin(ft_substr(tokens[*n].variable, 1, size, 0), "=", 1);
	read_from_history(n, tokens, needle, size);
	free(needle);
	if (!tokens[*n].expanded)
		return (1);
	return (0);
}

/*
Esta función establece los posibles parametros de la variable de expansión.
Para obtener el PID, simplemente cambiamos el token $$ por un comando que
mostrará el número del PID en ejecución. Si no encuentra ningún valor de
sustitución lo reemplazará por "". La función get_exit_status_variable
en principio debería recoger la variable global que se iría actualizando
cada vez que ejecutara un proceso con la salida de éste.
*/
void	get_variable_expansion_value(int *n, char **s, t_tokens *tokens)
{
	char	*token;

	token = s[*n];
	if (ft_strlen(token) == 1)
		tokens[*n].expanded = ft_strdup("'$'");
	else if (ft_strncmp(token, "$$", ft_strlen(token)) == 0)
		tokens[*n].expanded = \
		ft_strdup("ps -o ppid= | tail -n 1 | sed 's/^[[:space:]]*//'");
	// else if (ft_strncmp(token, "$?", ft_strlen(token)) == 0)
	// 	get_exit_status_variable();
	else if (get_variable_from_path(n, tokens) == 1)
		if (get_variable_from_history(n, tokens) == 1)
			tokens[*n].expanded = ft_strdup("");
	*n += 1;
}

int	main(void)
{
	t_tokens	*prueba;
	char		*str = "${HOME} $babalu ${HOME} $ARG";
	int			c;

	c = 0;
	printf("%d\n", variable_expansion_counter(str));
	prueba = variable_expansion_tokens(str);
	get_variable_expansion_value(&c, &str, prueba);

	int i = 0;
	while (prueba[i].variable != NULL)
	{
		printf("prueba_var[%d] = %s\n", i, prueba[i].variable);
		printf("prueba_exp[%d] = %s\n\n", i, prueba[i].expanded);
		i++;
	}
	printf("prueba_var[%d] = %s\n", i, prueba[i].variable);
	printf("prueba_exp[%d] = %s\n", i, prueba[i].expanded);
	return (0);
}
