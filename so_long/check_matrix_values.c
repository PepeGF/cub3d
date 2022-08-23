/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:21:39 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/29 19:58:24 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_values(t_board **board, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (board[i][j].type != 'C' && board[i][j].type != 'P' &&
				board[i][j].type != 'E' && board[i][j].type != '0' &&
				board[i][j].type != '1')
			{
				printf("Error\nCheck the matrix values\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	check_map_border(t_board **board, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (i == 0 || j == 0 || i == x - 1 || j == y - 1)
			{
				if (board[i][j].type != '1')
				{
					printf("Error\nCheck the border\n");
					exit(0);
				}
			}
			j++;
		}
		i++;
	}
}
