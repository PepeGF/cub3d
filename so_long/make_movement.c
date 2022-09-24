/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:57 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/24 12:18:23 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* void	end_game(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->player.x += x;
	data->player.y += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->dino,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->mov_cont += 1;
	// steps(data);
	exit (0);
} */

void	move_player(t_data *data, int y, int x)
{	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.y][data->player.x].col * data->px),
		(data->board[data->player.y][data->player.x].row * data->px));
	data->player.x += x;
	data->player.y += y;
	draw_player(*data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->dino,
	// 	(data->board[data->player.y][data->player.x].col * data->px),
	// 	(data->board[data->player.y][data->player.x].row * data->px));
	data->mov_cont += 1;
	// ft_get_player_position(&data->player, *data);
	// printf("Nueva posición: x: %d\ty: %d\n", data->player.x_position, data->player.y_position);
	// steps(data);
}

void	check_if_colleccionable(t_data *data)
{
	if (data->board[data->player.x][data->player.y].type == 'C')
	{
		data->cont->coll -= 1;
		data->board[data->player.x][data->player.y].type = '0';
	}
}
