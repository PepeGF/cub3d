/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:12:42 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 14:19:46 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_limits(unsigned long long n, int e)
{
	if (n > 9223372036854775807 && e == -1)
		return (0);
	if (n > 9223372036854775807 && e == 1)
		return (-1);
	return (n * e);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					e;
	unsigned long long	n;

	i = 0;
	e = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			e *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (ft_limits(n, e));
}
