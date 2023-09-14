/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:13 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:45:16 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**get_lexer(char *input, t_global *global)
{
	char	*new_input;
	char	**lexer;

	if (local_var(global, input) == 0)
		return (NULL);
	new_input = expansion_variable(input, global);
	lexer = lexer_maker(new_input);
	free_mem((void **)&new_input);
	return (lexer);
}
