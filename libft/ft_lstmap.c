/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:52:42 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:54:36 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*a;

	if (lst == NULL)
	{
		ft_lstclear(&lst, del);
		return (0);
	}
	a = 0;
	new = 0;
	while (lst != NULL)
	{
		a = ft_lstnew(f(lst->content));
		if (a == NULL)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, a);
		lst = lst->next;
	}
	return (new);
}
