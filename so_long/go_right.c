/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:07:03 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/27 20:13:48 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_right(t_data *data)
{
	if ((data->player.y + 1) < (data->cont->x - 1))
	{
		if (data->board[data->player.x][data->player.y + 1].type != '1')
		{
			if (data->board[data->player.x][data->player.y + 1].type == 'E')
			{
				if (data->cont->coll == 0)
					end_game(data, 0, 1);
			}
			else
			{
				move_player(data, 0, 1);
				check_if_colleccionable(data);
			}
		}
	}
}
