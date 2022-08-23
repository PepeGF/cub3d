/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:03:08 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 14:04:37 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*aux;
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	aux = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (aux == 0)
		return (0);
	while (i < ft_strlen(s))
	{
		aux[i] = f(i, s[i]);
		i++;
	}
	aux[i] = 0;
	return (aux);
}
