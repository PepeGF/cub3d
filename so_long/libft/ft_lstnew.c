/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:57:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:57:48 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lista;

	lista = malloc(sizeof(t_list));
	if (lista == 0)
		return (0);
	lista->content = content;
	lista->next = NULL;
	return (lista);
}
