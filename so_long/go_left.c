/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:14:47 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/27 20:16:08 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_left(t_data *data)
{
	if ((data->player.y - 1) > 0)
	{
		if (data->board[data->player.x][data->player.y - 1].type != '1')
		{
			if (data->board[data->player.x][data->player.y - 1].type == 'E')
			{
				if (data->cont->coll == 0)
					end_game(data, 0, -1);
			}
			else
			{
				move_player(data, 0, -1);
				check_if_colleccionable(data);
			}
		}
	}
}
