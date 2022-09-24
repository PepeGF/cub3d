/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:19:40 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/24 12:16:53 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_player_initial_direction(t_board **board, t_player player)
{
	if (board[player.y][player.x].type == 'N')
		return (90);
	if (board[player.y][player.x].type == 'S')
		return (270);
	if (board[player.y][player.x].type == 'W')
		return (180);
	if (board[player.y][player.x].type == 'E')
		return (0);
	else
		return (-1);	
}

int	is_player(t_board **board, int i, int j)
{
	if (board[i][j].type == 'N' || board[i][j].type == 'S'
		|| board[i][j].type == 'E' || board[i][j].type == 'W')
		return (1);
	return (0);
}

void	ft_get_player_initial_position(t_player *player, t_data data)
{
	player->x_position = player->x * data.px + data.px / 2;
	player->y_position = player->y * data.px + data.px / 2;
	// printf ("Posición del jugador:\n\tx: %d\n\ty: %d\n", player->x, player->y);
	return ;
}

void	ft_get_player_dir_vector(t_player *player, t_data data)
{
	player->x_dir_vect = cos(player->direction * 2 * M_PI / 360);
	player->y_dir_vect = -1 * sin(player->direction * 2 * M_PI / 360);
	gt_get_camera_vector(&data, player);
}

t_player	where_is_the_player(t_board **board, int x, int y, t_data data)
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
				// printf("player.x: %d\tplayer.y: %d\tpx: %d\n", player.x, player.y, data.px);
				player.direction = ft_player_initial_direction(board, player);
				ft_get_player_initial_position(&player, data); //con movimiento fluido esto solo vale para el inicio
				ft_get_player_dir_vector(&player, data);
				break ;
			}	
			j++;
		}
	}
	return (player);
}
