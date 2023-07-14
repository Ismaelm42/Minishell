/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:18:39 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/01/05 17:06:36 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_string_counter(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static unsigned int	ft_string_start(char *s, char c, unsigned int start)
{
	while (s[start] != '\0' && s[start] == c)
		start++;
	return (start);
}

static size_t	ft_string_len(char *s, char c, unsigned int start)
{
	size_t	i;

	i = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

void	ft_free(char **str, int n)
{
	while (n > 0)
	{
		free (str[n - 1]);
		n--;
	}
	free (str);
}

char	**ft_split(char *s, char c)
{
	unsigned int	start;
	int				n;
	char			**str;

	start = 0;
	n = 0;
	str = malloc(sizeof(char **) * (ft_string_counter(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (n < ft_string_counter(s, c))
	{
		start = ft_string_start(s, c, start);
		str[n] = ft_substr(s, start, (size_t)ft_string_len(s, c, start), 0);
		if (str[n] == NULL)
		{
			ft_free(str, n);
			return (NULL);
		}
		n++;
		start = start + ft_string_len(s, c, start);
	}
	str[n] = 0;
	return (str);
}
