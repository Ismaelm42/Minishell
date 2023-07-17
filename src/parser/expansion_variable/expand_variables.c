#include "../../../include/minishell.h"

/*
Obtiene la variable a través del Path. También controla en caso de que la variable
haya sido enviada entre paréntesis: ${HOME}
*/
int	get_variable_from_path(int n, t_tokens *tokens)
{
	char	*copy;
	char	*environment;

	copy = ft_substr(tokens[n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	environment = getenv(copy);
	if (environment == NULL)
		return (1);
	tokens[n].expanded = ft_strdup(environment);
	free(copy);
	return (0);
}

/*
Crea needle que es nombre de la variable más el símbolo igual para poder
buscarlo por el historial en la función read_from_history.
Ejemplo de needle: ARG= 
*/
int	get_variable_from_history(int n, t_tokens *tokens)
{
	char	*needle;
	int		size;

	size = ft_strlen(tokens[n].variable);
	needle = ft_substr(tokens[n].variable, 1, size, 0);
	if (needle[0] == '{' && needle[ft_strlen(needle) - 1] == '}')
	{
		needle = ft_strtrim(needle, "{", 1);
		needle = ft_strtrim(needle, "}", 1);
		size -= 2;
	}
	needle = ft_strjoin(needle, "=", 1);
	read_from_history(n, tokens, needle, size);
	free(needle);
	if (!tokens[n].expanded)
		return (1);
	return (0);
}

/*
Esta función establece los posibles parametros de la variable $.
Para obtener el PID, simplemente cambiamos el token $$ por un comando que
mostrará el número del PID en ejecución. Si no encuentra ningún valor de
sustitución lo reemplazará por "". La función get_exit_status_variable
en principio debería recoger la variable global que se iría actualizando
cada vez que ejecutara un proceso con la salida de éste.
*/
void	get_variable_expansion_value(int n, t_tokens *tokens)
{
	char	*token;

	token = tokens[n].variable;
	if (ft_strlen(token) == 1)
		tokens[n].expanded = ft_strdup("'$'");
	else if (ft_strncmp(token, "$$", ft_strlen(token)) == 0)
		tokens[n].expanded = \
		ft_strdup("ps -o ppid= | tail -n 1 | sed 's/^[[:space:]]*//'");
	// else if (ft_strncmp(token, "$?", ft_strlen(token)) == 0)
	// 	get_exit_status_variable();
	else if (get_variable_from_path(n, tokens) == 1)
		if (get_variable_from_history(n, tokens) == 1)
			tokens[n].expanded = ft_strdup("");
}

/*
Se encarga de realizar todo el procedimiento para expandir la variable $.
En esta función, se realizan todas las demás de la carpeta src/expand_variables.
Una vez realizada la llamada a esta función, obtenemos un nuevo input modificado
con los valores reales de $.
*/
char	*expansion_variable(char *input)
{
	t_tokens	*tokens;
	char		*new_input;
	int			size;
	int			i;

	if (variable_expansion_counter(input) != 0)
	{
		tokens = get_variable_expansion_tokens(input);
		size = variable_expansion_counter(input);
		i = 0;
		while (i < size)
		{
			get_variable_expansion_value(i, tokens);
			i++;
		}
		new_input = replace_variables(input, tokens);
		free(input);
		if (variable_expansion_counter(new_input) != 0)
			new_input = expansion_variable(new_input);
		free_expansion_tokens(size, tokens, 1);
		return (new_input);
	}
	else
		return (input);
}
