/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:19:40 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/28 20:21:52 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_player(t_board **board, int i, int j)
{
	if (board[i][j].type == 'P')
		return (1);
	return (0);
}

t_player	where_is_the_player(t_board **board, int x, int y)
{
	int			i;
	int			j;
	t_player	player;

	player.x = -1;
	player.y = -1;
	i = -1;
	while (++i < x)
	{
		j = 0;
		while (j < y)
		{
			if (is_player(board, i, j))
			{
				player.y = j;
				player.x = i;
				break ;
			}	
			j++;
		}
	}
	return (player);
}
