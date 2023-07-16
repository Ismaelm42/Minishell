#include "../../../include/minishell.h"


/*

*/
void	get_size_variables(int *variable, int *expanded, char *input, t_tokens *tokens)
{
	char	*tokens_ptr;
	int		i;
	int		n;

	tokens_ptr = input;
	i = 0;
	*variable = 0;
	*expanded = 0;
	while (tokens[i].variable != NULL)
	{
		*variable += ft_strlen(tokens[i].variable);
		*expanded += ft_strlen(tokens[i].expanded);
		tokens_ptr = ft_strnstr(tokens_ptr, tokens[i].variable, 1000);
		tokens[i].position = tokens_ptr - input;
		n = 0;
		while (tokens_ptr && n < ft_strlen(tokens[i].variable))
		{
			tokens_ptr++;
			n++;
		}
		i++;
	}
}
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
			// printf("position[%d]\n", tokens[j].position);
			// printf("token[%d] = %s\n", j, tokens[j].expanded);
			n = 0;
			while (tokens[j].expanded[n] != 0)
			{
				new_input[k] = tokens[j].expanded[n];
				k++;
				n++;
			}
			i += ft_strlen(tokens[j].variable);
			j++;
		}
		else
		{
			new_input[k] = input[i];
			i++;
			k++;
		}
	}
}

void	replace_variables(char *input, t_tokens *tokens)
{
	char	*new_input;
	int		input_size;
	int		var_size;
	int		exp_size;
	int		size;

	input_size = ft_strlen(input);
	get_size_variables(&var_size, &exp_size, input, tokens);
	size = (input_size - var_size + exp_size);
	printf("size = %d\n", size);
	new_input = (char *)calloc(sizeof(char), size + 1);
	printf("%s\n", input);
	replace_function(new_input, input, tokens);
	printf("%s\n", new_input);
	printf("sizedef = %d\n", ft_strlen(new_input));
}

int	main(void)
{
	char *input = ft_strdup("$NOARG $$ $   $12345 $ARG ${ARG} $HOME ${LOGNAME}  $PWD ");


	expansion_variable(input);


}
