#include "../../../include/minishell.h"

/*
Función para liberar la memoria. Se resta primero para bajar un nivel más
ya que en n es donde ha fallado la memoria.
*/
t_tokens	*free_expansion_tokens(int n, t_tokens *tokens, int flag)
{
	while (n > 0)
	{
		n--;
		free (tokens[n].variable);
		if (flag != 0)
			free (tokens[n].variable);
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

/*
Busca en la cadena input si existen variables $ que no estén precedidas y seguidas por comillas.
En caso de que sí hubiera, devuelve 1.
*/
int	search_for_more_sign_dollars(char *input)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == '$')
			if ((input[i - 1] != '\'' && (i - 1) != -1)
				|| (input[i + 1] != '\'' && input[i + 1] != 0))
				return (1);
		i++;
	}
	return (0);
}
