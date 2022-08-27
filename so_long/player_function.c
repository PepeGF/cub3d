/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:19:40 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 14:04:02 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_player_direction(t_board **board, t_player player)
{
	if (board[player.y][player.x].type == 'N')
		return (90);
	if (board[player.y][player.x].type == 'S')
		return (270);
	if (board[player.y][player.x].type == 'W')
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

// int	*ft_get_player_position(board, player)
// {
// 	int	aux[2];

// 	aux[0] = 
// }

t_player	where_is_the_player(t_board **board, int x, int y)
{
	int			i;
	int			j;
	t_player	player;

	i = -1;
	while (++i < y)
	{
		j = 0;
		while (j < x)
		{
			if (is_player(board, i, j))
			{
				player.x = j;
				player.y = i;
				player.direction = ft_player_direction(board, player);
				// player.position = ft_get_player_position(board, player);
				// player.dir_vector = ft_get_player_direction(board, player);
				break ;
			}	
			j++;
		}
	}
	return (player);
}
