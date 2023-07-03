/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:40:24 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/01/04 12:52:50 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	char	*str_dst;
	char	*str_src;	
	size_t	i;

	str_dst = (char *)dst;
	str_src = (char *)src;
	i = 0;
	if (dstsize != '\0')
	{	
		while (str_src[i] != '\0' && i < (dstsize - 1))
		{
			str_dst[i] = str_src[i];
			i++;
		}
		str_dst[i] = '\0';
	}
	return (ft_strlen(src));
}
