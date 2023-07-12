#include "../../include/minishell.h"


// int		get_variable_from_path();
// int		get_variable_from_history();
// void	get_pid_variable();
// void	get_exit_status_variable();


// void	get_variable_expansion_value(int *n, char **s, char ***tokens)
// {
// 	char	*token;

// 	token = *s[*n];
// 	if (ft_strlen(token) == 1)
// 		(*tokens)[*n] = ft_strdup(token);
// 	else if (ft_strncmp(token, "$$", ft_strlen(token)) == 0)
// 		get_pid_variable();
// 	else if (ft_strncmp(token, "$?", ft_strlen(token)) == 0)
// 		get_exit_status_variable();
// 	else
// 	{
// 		if (get_variable_from_path() == 1)
// 			if (get_variable_from_history() == 1)
// 				error;
// 	}
// 	*n += 1;
// }









// int	main(void)
// {
// 	char	**prueba;
// 	char	*str = "$'$''$hola'3232 '$ARGCOMILLAS'  $$$ARG3   $?$ARG4    $";

// 	printf("%d\n", variable_expansion_counter(str));
// 	prueba = variable_expansion_tokens(str);

// 	int i = 0;
// 	while (prueba[i] != NULL)
// 	{
// 		printf("prueba[%d] = %s\n", i, prueba[i]);
// 		i++;
// 	}
// 	printf("prueba[%d] = %s\n", i, prueba[i]);
// 	return (0);
// }

//expandir la variable primero por el path
//luego por historial
//realizar el cambio en el input para mandarlo al token_maker
//estructura para no tener que hacer un split de nuevo mejor, que ya está bien con los que llevo








// void	new_expansion_tokens(char **tokens)
// {
// 	char	**new_tokens;
// 	int		n;
// 	int		size;

// 	while (tokens[size] != NULL)
// 		size++;
// 	new_tokens = (char **)malloc(sizeof(char *) * size + 1);
// 	n = 0;
// 	while (n < size)
// 	{
// 		get_variable_expansion_value(&n, &tokens, &new_tokens);
// 		if (!new_tokens[n - 1])
// 			return (free_tokens(n - 1, new_tokens));
// 	}
// 	new_tokens[n] = NULL;
// 	return (new_tokens);
// }
