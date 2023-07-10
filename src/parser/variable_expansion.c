#include "../../include/minishell.h"

int	check_variable_expansion_symbol(char *input)
{
	char	*ptr;
	int		single_quotes_counter;

	single_quotes_counter = 0;
	ptr = ft_strchr(input, '$');
	if (ptr == NULL)
		return (-1);
	while (ft_strchr(ptr, '\'') != NULL)
	{
		ptr = ft_strchr(ptr, '\'');
		ptr++;
		single_quotes_counter++;
	}
	if (single_quotes_counter == 0 || single_quotes_counter % 2 == 0)
		return (0);
	return (1);
}



// int	main(void)
// {
// 	char	*str = "      ' $hola  '      ";

// 	printf("%d\n", check_variable_expansion_symbol(str));
// 	return (0);
// }

//gnl tiene que leer hasta el final para comprobar que la variable no se haya machacado.
