/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:20:30 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/24 13:42:13 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static void	ft_string(char *s, unsigned int num, int i, int n)
{
	while (i > 0 && num > 9)
	{
		s[i] = (num % 10) + 48;
		num = num / 10;
		i--;
	}
	s[i] = num + 48;
	if (n < 0)
		s[0] = '-';
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	size_t			co;
	char			*s;
	size_t			i;

	co = ft_count(n);
	if (n == -2147483648)
	{
		s = ft_strdup("-2147483648");
		return (s);
	}
	s = malloc(sizeof(char) * (co + 1));
	if (s == 0)
		return (0);
	if (n < 0)
		num = n * (-1);
	else
		num = n;
	i = co - 1;
	s[co] = '\0';
	ft_string(s, num, co - 1, n);
	return (s);
}
