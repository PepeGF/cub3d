/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:19:40 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/23 18:35:13 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_player_direction(t_board **board, t_player player)
{
	if (board[player.x][player.y].type == 'N')
		return (90);
	if (board[player.x][player.y].type == 'S')
		return (270);
	if (board[player.x][player.y].type == 'W')
		return (180);
	else
		return (0);	
}

int	is_player(t_board **board, int i, int j)
{
	if (board[i][j].type == 'N' || board[i][j].type == 'S'
		|| board[i][j].type == 'E' || board[i][j].type == 'W')
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
				player.direction = ft_player_direction(board, player);
				printf("Esta orientado hacia %d\n", player.direction);
				break ;
			}	
			j++;
		}
	}
	return (player);
}
