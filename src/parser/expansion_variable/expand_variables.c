#include "../../../include/minishell.h"

/*
Obtiene la variable a través del Path. También controla en caso de que la variable
haya sido enviada entre paréntesis: ${HOME}
*/
int	get_variable_from_env(int n, t_lexer *lexer, t_global *global)
{
	char	*copy;
	char	*environment;

	copy = ft_substr(lexer[n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	environment = search_env_expand(copy, global->env);
	free_mem((void **)&copy);
	if (environment == NULL)
		return (1);
	lexer[n].expanded = ft_strdup(environment);
	free_mem((void **)&environment);
	return (0);
}

int	get_variable_from_local_var(int n, t_lexer *lexer, t_global *global)
{
	char	*copy;
	char	*var;

	copy = ft_substr(lexer[n].variable, 1, 1000, 0);
	if (copy[0] == '{' && copy[ft_strlen(copy) - 1] == '}')
	{
		copy = ft_strtrim(copy, "{", 1);
		copy = ft_strtrim(copy, "}", 1);
	}
	var = search_key(global->lst_local, copy);
	free_mem((void **)&copy);
	if (var == NULL)
		return (1);
	lexer[n].expanded = ft_strdup(var);
	return (0);
}

/*
Esta función establece los posibles parametros de la variable $.
Para obtener el PID, simplemente cambiamos el lex $$ por un comando que
mostrará el número del PID en ejecución. Si no encuentra ningún valor de
sustitución lo reemplazará por "". La función get_exit_status_variable
en principio debería recoger la variable global que se iría actualizando
cada vez que ejecutara un proceso con la salida de éste.
*/
void	get_expansion_value(int n, t_lexer *lexer, t_global *global)
{
	char	*lex;

	lex = lexer[n].variable;
	if (ft_strlen(lex) == 1)
		lexer[n].expanded = ft_strdup("'$'");
	// else if (ft_strncmp(lex, "$?", ft_strlen(lex)) == 0)
	// 	get_exit_status_variable();
	else if (get_variable_from_env(n, lexer, global) == 1)
		if (get_variable_from_local_var(n, lexer, global) == 1)
			lexer[n].expanded = ft_strdup("");
}

/*
Se encarga de realizar todo el procedimiento para expandir la variable $.
En esta función, se realizan todas las demás de la carpeta src/expand_variables.
Una vez realizada la llamada a esta función, obtenemos un nuevo input modificado
con los valores reales de $.
*/
char	*expansion_variable(char *input, t_global *global)
{
	t_lexer		*lexer;
	char		*new_input;
	int			size;
	int			i;

	if (variable_expansion_counter(input) != 0)
	{
		lexer = get_variable_expansion_lexer(input);
		size = variable_expansion_counter(input);
		i = 0;
		while (i < size)
		{
			get_expansion_value(i, lexer, global);
			i++;
		}
		new_input = replace_variables(input, lexer);
		free_expansion_lexer(lexer, 1);
		if (variable_expansion_counter(new_input) != 0)
			new_input = expansion_variable(new_input, global);
		return (new_input);
	}
	else
		return (input);
}
