/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:06 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/10/02 16:21:48 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_variables(t_list **list)
{
	t_list	*aux;

	// aux = *list;
	while (*list)
	{
		aux = (*list)->next;
		if ((*list)->content != NULL)
			free((*list)->content);
		free(*list);
		*list = aux;
	}
}

void	free_variables_board(t_board **list, int fil)
{
	int		i;

	i = 0;
	while (i < fil)
	{
		free(list[i]);
		i++;
	}
	free(list);
}
