/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:57 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/26 20:22:28 by josgarci         ###   ########.fr       */
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

void	turn(t_data *data, int keycode)
{
	data->player.turn_speed = 5;
	if (keycode == key_right)
		data->player.turn_on = -1;
	else
		data->player.turn_on = 1;
	data->player.direction += data->player.turn_speed * data->player.turn_on;
	// printf("%d, %d, %d\n", data->player.direction, data->player.turn_speed, data->player.turn_on);
	data->player.direction %= 360;
	if (data->player.direction < 0)
		data->player.direction += 360;
	printf("Direccion: %d\n", data->player.direction);
}

void	front_back(t_data *data, int keycode)
{
	data->player.move_speed = 3;
	if (keycode == key_w || keycode == key_up)
		data->player.turn_on = 1;
	else
		data->player.turn_on = -1;
	data->player.x_position += cos(data->player.direction * M_PI / 180) * data->player.move_speed * data->player.turn_on;
	data->player.y_position += -1 * sin(data->player.direction * M_PI / 180) * data->player.move_speed * data->player.turn_on; //el -1 de antes de sin es xq el sentido positivo de las y es hacia abajo
	printf("Nueva X: %d\tnueva y: %d\n", data->player.x_position, data->player.y_position);
	draw_player(*data);
}

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
