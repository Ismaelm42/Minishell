#include "../../../include/minishell.h"


// int		get_variable_from_path();
// int		get_variable_from_history();
// void		get_exit_status_variable();

/*
Esta función establece los posibles parametros de la variable de expansión.
Para obtener el PID, simplemente cambiamos el token $$ por un comando que
mostrará el número del PID en ejecución. Si no encuentra ningún valor de
sustitución lo reemplazará por "". La función get_exit_status_variable
en principio debería recoger la variable global que se iría actualizando
cada vez que ejecutara un proceso con la salida de éste.
*/

int	get_variable_from_path(int *n, t_tokens *tokens)
{
	char	*copy;
	char	*environment;

	copy = tokens[*n].variable;
	copy++;
	environment = getenv(copy);
	if (environment == NULL)
		return (1);
	tokens[*n].expanded = ft_strdup(environment);
	return (0);
}

int	get_variable_from_history(int *n, t_tokens *tokens)
{
	printf("mierda pa ti! %d %s\n", *n, tokens[*n].variable);
	return (0);
}

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

// int	main(void)
// {
// 	t_tokens	*prueba;
// 	char		*str = "$PATH";
// 	int			c;

// 	c = 0;
// 	printf("%d\n", variable_expansion_counter(str));
// 	prueba = variable_expansion_tokens(str);
// 	get_variable_expansion_value(&c, &str, prueba);

// 	int i = 0;
// 	while (prueba[i].variable != NULL)
// 	{
// 		printf("prueba[%d] = %s\n", i, prueba[i].variable);
// 		i++;
// 	}
// 	printf("prueba[%d] = %s\n", i, prueba[i].variable);

// 	return (0);
// }

