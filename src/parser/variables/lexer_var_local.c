/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var_local.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:47:25 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:47:26 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**var_lexer_maker(char *s)
{
	char	**lexer;
	int		size;
	int		n;

	n = 0;
	size = var_lexer_counter(s);
	lexer = (char **)ft_calloc(sizeof(char **), size + 1);
	while (n < size)
	{
		if (*s == '\'' || *s == '"')
			var_quoted_lexer_splitter(&n, &s, &lexer);
		else
			var_words_splitter(&n, &s, &lexer);
		if (!lexer[n - 1])
			return (free_matrix((void ***)&lexer, 0));
	}
	lexer[n] = 0;
	return (lexer);
}
