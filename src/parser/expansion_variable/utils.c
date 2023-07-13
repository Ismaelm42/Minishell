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
