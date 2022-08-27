/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:14:47 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 13:41:02 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_left(t_data *data)
{
	if ((data->player.x - 1) > 0)
	{
		if (data->board[data->player.y][data->player.x - 1].type != '1')
		{
			/* if (data->board[data->player.x][data->player.y - 1].type == 'E')
			{
				if (data->cont->coll == 0)
					end_game(data, 0, -1);
			}
			else */
			{
				move_player(data, 0, -1);
				// check_if_colleccionable(data);
			}
		}
	}
}
