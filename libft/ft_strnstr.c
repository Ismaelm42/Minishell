/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:41:02 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/01/05 12:55:14 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	j = 0;
	while (haystack[j] != '\0' && j < len)
	{
		i = 0;
		if (needle[i] == haystack[j])
		{
			while (i + j < len && needle[i] == haystack[i + j])
			{
				i++;
				if (i == (size_t)ft_strlen(needle))
					return ((char *)&haystack[j]);
			}
		}
		j++;
	}
	return (0);
}
