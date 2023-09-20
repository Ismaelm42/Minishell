/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javier <javier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:56:05 by javier            #+#    #+#             */
/*   Updated: 2023/09/20 10:56:08 by javier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_wildcards(char **lexer)
{
	int	i;

	i = 0;
	while (lexer[i] != NULL)
	{
		if (ft_strchr(lexer[i], '*') != NULL)
			return (1);
		i++;
	}
	return (0);
}

char	**get_dir_content(void)
{
	DIR				*directory;
	struct dirent	*content;
	char			**dir_content;
	int				n;

	n = 0;
	directory = opendir(".");
	if (directory == NULL)
		return (NULL);
	while (readdir(directory) != NULL)
		n++;
	closedir(directory);
	directory = opendir(".");
	if (directory == NULL)
		return (NULL);
	dir_content = (char **) ft_calloc(sizeof(char *), n + 1);
	n = 0;
	content = readdir(directory);
	while (content != NULL)
	{
		dir_content[n++] = ft_strdup(content->d_name);
		content = readdir(directory);
	}
	dir_content[n] = NULL;
	return (closedir(directory), dir_content);
}

int	check_wildcard_conditions(char *lexer)
{
	int		i;
	char	c;

	i = 0;
	while (lexer[i] != '\0')
	{
		if (lexer[i] == '\'' || lexer[i] == '\"')
		{
			c = lexer[i++];
			while (lexer[i] != '\0' && lexer[i] != c)
			{
				if (lexer[i] == '*')
					return (1);
				i++;
			}
			if (lexer[i] == c)
				c = 0;
		}
		i++;
	}
	return (0);
}

int	extract_wildcards(char **lexer, char **dir, int flag)
{
	char	*substr;
	char	*dir_ptr;
	int		length;

	dir_ptr = *dir;
	if (ft_strchr(*lexer, '*') != NULL)
		length = ft_strchr(*lexer, '*') - *lexer;
	else
		length = ft_strlen(*lexer);
	substr = ft_substr(*lexer, 0, length, 0);
	*dir = ft_strnstr(*dir, substr, ft_strlen(*dir));
	if (*dir == NULL || (flag == 0 \
	&& ft_strncmp(dir_ptr, *dir, ft_strlen(dir_ptr)) != 0))
		return (free_mem((void **)&substr), 1);
	*dir += length;
	if (length == ft_strlen(*lexer))
		while (ft_strnstr(*dir, substr, ft_strlen(*dir)) != NULL)
			*dir = ft_strnstr(*dir, substr, ft_strlen(*dir)) + length;
	*lexer += length;
	free_mem((void **)&substr);
	return (0);
}
