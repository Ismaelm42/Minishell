/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:24 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:55:17 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	token_maker(t_token *tokens, char **lexer);

static void	token_maker(t_token *tokens, char **lexer)
{
	int	*size;

	while (*lexer != NULL)
	{
		size = token_counter(lexer);
		allocate_token_memory(tokens, size);
		token_filler(tokens, lexer);
		advance_lexer_tokens(&lexer, &tokens);
	}
}

int	get_tokens(char *input, t_global *global)
{
	t_token	*tokens;
	char	**lexer;
	int		return_n;
	int		n;

	lexer = get_lexer(input, global);
	if (lexer == NULL)
		return (1);
	return_n = syntax_error_check(lexer);
	if (return_n != 0)
		return (free_matrix((void ***)&lexer, 0), return_n);
	lexer = get_wildcards(lexer);
	n = lexer_pipes_counter(lexer);
	tokens = (t_token *)ft_calloc(sizeof(t_token), n + 1);
	token_maker(tokens, lexer);
	global->pipeline = n;
	global->tokens = tokens;
	free_matrix((void ***)&lexer, 0);
	return (0);
}
