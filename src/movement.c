/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:30:09 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 20:36:40 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	turn(t_data *data, int keycode)
{
	data->player->turn_speed = TURN_SPEED;
	if (keycode == key_right)
		data->player->turn_on = -1;
	else
		data->player->turn_on = 1;
	data->player->direction += data->player->turn_speed * data->player->turn_on;
	data->player->direction %= 360;
	if (data->player->direction < 0)
		data->player->direction += 360;
	data->player->dir_rad = data->player->direction * M_PI / 180;
	data->player->dir_x = cos(data->player->dir_rad);
	data->player->dir_y = -sin(data->player->dir_rad);
	data->player->plane_x = 0.66 * cos(data->player->dir_rad + M_PI_2);
	data->player->plane_y = -0.66 * sin(data->player->dir_rad + M_PI_2);
	raycast(data, data->ray, data->player);
}

void	front_back(t_data *data, int keycode)
{
	int	player_pos_x_temp;
	int	player_pos_y_temp;

	data->player->move_speed = MOVE_SPEED;
	if (keycode == key_w || keycode == key_up)
		data->player->move_on = 1;
	else
		data->player->move_on = -1;
	player_pos_x_temp = (int)(data->player->x_position
			+ roundf(cos(data->player->direction * M_PI / 180)
				* data->player->move_speed * data->player->move_on));
	player_pos_y_temp = (int)(data->player->y_position
			+ roundf((-1 * sin(data->player->direction * M_PI / 180)
					* data->player->move_speed * data->player->move_on)));
	get_future_pos_from_player_pixel(data, player_pos_x_temp,
		player_pos_y_temp);
	if (check_x_collision(data, player_pos_x_temp) == 0)
		data->player->x_position = player_pos_x_temp;
	if (check_y_collision(data, player_pos_y_temp) == 0)
		data->player->y_position = player_pos_y_temp;
	set_current_grid(data);
	raycast(data, data->ray, data->player);
}

void	side_move(t_data *data, int keycode)
{
	int	player_pos_x_temp;
	int	player_pos_y_temp;

	data->player->move_speed = MOVE_SPEED;
	if (keycode == key_d)
		data->player->sideway_on = 1;
	else
		data->player->sideway_on = -1;
	player_pos_x_temp = (int)(data->player->x_position
			+ roundf(cos(((data->player->direction + 270) % 360) * M_PI / 180)
				* data->player->move_speed * data->player->sideway_on));
	player_pos_y_temp = (int)(data->player->y_position
			+ roundf((-1 * sin(((data->player->direction + 270) % 360) * M_PI
						/ 180) * data->player->move_speed
					* data->player->sideway_on)));
	get_future_pos_from_player_pixel(data, player_pos_x_temp,
		player_pos_y_temp);
	if (check_x_collision(data, player_pos_x_temp) == 0)
		data->player->x_position = player_pos_x_temp;
	if (check_y_collision(data, player_pos_y_temp) == 0)
		data->player->y_position = player_pos_y_temp;
	set_current_grid(data);
	raycast(data, data->ray, data->player);
}

int	get_future_pos_from_player_pixel(t_data *data, int player_pos_x_temp,
	int player_pos_y_temp)
{
	data->player->x_fut = player_pos_x_temp / data->px;
	data->player->y_fut = player_pos_y_temp / data->px;
	return (0);
}

void	set_current_grid(t_data *data)
{
	data->player->x = data->player->x_position / (float)data->px;
	data->player->y = data->player->y_position / (float)data->px;
}
