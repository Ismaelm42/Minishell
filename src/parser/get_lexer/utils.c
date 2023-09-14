/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:45:47 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:45:48 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	reject_quotes(char *s, char *substr, int *i, int *j)
{
	char	c;

	c = 0;
	if (s[(*j)] == '\'' || s[(*j)] == '\"')
	{
		c = s[(*j)++];
		while (s[(*j)] != c && s[(*j)] != '\0')
			substr[(*i)++] = s[(*j)++];
		if (s[(*j)] != '\0')
		{
			c = 0;
			(*j)++;
		}
	}
	return (c);
}

void	check_quotes(char *s, int *length)
{
	char	c;

	c = 0;
	if (s[(*length)] == '\'' || s[*length] == '\"')
	{
		c = s[(*length)++];
		while (s[*length] != '\0' && s[*length] != c)
			(*length)++;
		if (s[*length] != '\0')
			(*length)++;
	}
}
