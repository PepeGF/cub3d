/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:38:05 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 13:39:09 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_down(t_data *data)
{
	if ((data->player.y + 1) < (data->cont->y - 1))
	{
		if (data->board[data->player.y + 1][data->player.x].type != '1')
		{
			/* if (data->board[data->player.x + 1][data->player.y].type == 'E')
			{
				if (data->cont->coll == 0)
					end_game(data, 1, 0);
			}
			else */
			{
				move_player(data, 1, 0);
				// check_if_colleccionable(data);
			}
		}
	}
}
