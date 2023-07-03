/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:02:27 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/01/04 12:52:13 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;	
	char	*str;
	char	a;

	i = 0;
	str = (char *)b;
	a = (char)c;
	while (i < n)
	{
		str[i] = a;
		i++;
	}
	return (str);
}
