/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:10:17 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 14:12:00 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			a;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	num = n;
	if (num > 0 && num < 10)
	{
		a = num + 48;
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd(num / 10, fd);
		a = (num % 10) + 48;
		write(fd, &a, 1);
	}
}
