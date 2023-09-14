/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:39 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:46:40 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	lexer_pipes_counter(char **lexer)
{
	int	size;

	size = 0;
	while (*lexer != NULL)
	{
		if (*lexer[0] == '|')
			size++;
		lexer++;
	}
	return (size + 1);
}

void	redirection_and_command_token_counter(char ***lexer, int **size)
{
	if (ft_strncmp(**lexer, "<", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, ">", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, "<<", ft_strlen(**lexer)) == 0
		|| ft_strncmp(**lexer, ">>", ft_strlen(**lexer)) == 0)
	{
		(*size)[0]++;
		(*lexer)++;
	}
	else if ((*size)[1] == 0)
		(*size)[1]++;
	else
		(*size)[2]++;
}

int	*token_counter(char **lexer)
{
	int	*size;

	size = (int *)ft_calloc(sizeof(int), 3);
	while (*lexer != NULL && ft_strncmp(*lexer, "|", ft_strlen(*lexer)) != 0)
	{
		redirection_and_command_token_counter(&lexer, &size);
		lexer++;
	}
	return (size);
}
