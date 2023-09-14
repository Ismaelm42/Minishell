/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:46 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:52:06 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		get_size_variables(int *var, int *exp, t_lexer *lexer);
static void		replace_function(char *new_input, char *input, t_lexer *lexer);

static void	get_size_variables(int *var, int *exp, t_lexer *lexer)
{
	int		i;

	i = 0;
	*var = 0;
	*exp = 0;
	while (lexer[i].variable != NULL)
	{
		*var += ft_strlen(lexer[i].variable);
		*exp += ft_strlen(lexer[i].expanded);
		i++;
	}
}

static void	replace_function(char *new_input, char *input, t_lexer *lexer)
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
		if (i == lexer[j].position)
		{
			n = 0;
			while (lexer[j].expanded[n] != 0)
				new_input[k++] = lexer[j].expanded[n++];
			i += ft_strlen(lexer[j++].variable);
		}
		else
			new_input[k++] = input[i++];
	}
}

char	*replace_variables(char *input, t_lexer *lexer)
{
	char	*new_input;
	int		input_size;
	int		var_size;
	int		exp_size;
	int		size;

	input_size = ft_strlen(input);
	get_size_variables(&var_size, &exp_size, lexer);
	size = (input_size - var_size + exp_size);
	new_input = (char *)ft_calloc(sizeof(char), size + 1);
	replace_function(new_input, input, lexer);
	free_mem((void **)&input);
	return (new_input);
}
