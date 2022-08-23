/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:59:49 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 14:18:05 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char *)dst;
	s2 = (char *)src;
	if (dst == src)
		return (0);
	if (s2 < s1)
	{
		while (len > 0)
		{
			len--;
			s1[len] = s2[len];
		}
		return (s1);
	}
	while (i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s1);
}
