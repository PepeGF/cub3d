/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:18:32 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/24 16:49:03 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	steps(t_data *data)
{
	print_steps(*data);
	printf("\rSteps: %d\n", data->mov_cont);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 49 || keycode == 12)
		exit_game(data);
	if (keycode == 1 || keycode == 125)
		go_down(data);
	if (keycode == 13 || keycode == 126)
		go_up(data);
	if (keycode == 2)
		go_right(data);
	if (keycode == 0)
		go_left(data);
	return (0);
}
