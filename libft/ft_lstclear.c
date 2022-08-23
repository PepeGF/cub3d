/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:47:17 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:49:48 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*s;
	t_list	*a;

	if (*lst == NULL)
		return ;
	a = *lst;
	while (a != NULL)
	{
		s = a->next;
		del(a->content);
		free(a);
		a = s;
	}
	*lst = NULL;
}
