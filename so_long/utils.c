/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:31:44 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 14:04:21 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_list(t_list **list)
{
	t_list	*aux;

	aux = (*list);
	while (aux)
	{
		printf("%s", aux->content);
		aux = aux->next;
	}
}

void	print_matrix(t_board **matrix, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	printf("Matrix: x = %d, y = %d\n", x, y);
	while (++i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%c", matrix[i][j].type);
			j++;
		}
		printf("\n");
	}
}
