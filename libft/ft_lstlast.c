/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:51:52 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:52:22 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*ant;
	t_list	*sig;

	if (lst == 0)
		return (0);
	i = 0;
	ant = lst;
	if (ft_lstsize(lst) > 1)
	{
		sig = lst->next;
		while (sig != NULL)
		{
			ant = sig;
			sig = sig->next;
		}
	}
	return (ant);
}
