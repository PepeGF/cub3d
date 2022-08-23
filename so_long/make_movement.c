/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:57 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/29 19:48:49 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(t_data *data, int x, int y)
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
	steps(data);
	exit (0);
}

void	move_player(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->player.x += x;
	data->player.y += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->dino,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->mov_cont += 1;
	steps(data);
}

void	check_if_colleccionable(t_data *data)
{
	if (data->board[data->player.x][data->player.y].type == 'C')
	{
		data->cont->coll -= 1;
		data->board[data->player.x][data->player.y].type = '0';
	}
}
