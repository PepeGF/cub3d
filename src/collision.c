/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:30:58 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 20:36:43 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_x_collision(t_data *data, int player_pos_x_temp)
{
	data->player->x_fut = player_pos_x_temp / data->px;
	data->player->y_fut = data->player->y_position / data->px;
	if (data->board[data->player->y_fut][data->player->x_fut].type == '1')
	{
		return (1);
	}
	else
		return (0);
}

int	check_y_collision(t_data *data, int player_pos_y_temp)
{
	data->player->y_fut = player_pos_y_temp / data->px;
	data->player->x_fut = data->player->x_position / data->px;
	if (data->board[data->player->y_fut][data->player->x_fut].type == '1')
	{
		return (1);
	}
	return (0);
}
