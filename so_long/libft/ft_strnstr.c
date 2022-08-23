/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:54:37 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/17 08:54:41 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != 0)
	{
		if (haystack[i] == needle[j])
			j++;
		else
		{
			i = i - j;
			j = 0;
		}
		if (j == ft_strlen(needle))
			return ((char *)&haystack[i - j + 1]);
		i++;
	}
	return (0);
}
