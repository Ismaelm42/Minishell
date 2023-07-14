/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoro-sa <imoro-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:19:07 by imoro-sa          #+#    #+#             */
/*   Updated: 2023/01/04 12:53:26 by imoro-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char *s1, char *set, int flag)
{
	char			*str_trimmed;
	size_t			start;
	size_t			end;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) != 0 && s1[start] != 0)
		start++;
	while (ft_strchr(set, s1[end]) != 0 && end > start)
		end--;
	str_trimmed = ft_substr(s1, start, (end - start + 1), flag);
	return (str_trimmed);
}
