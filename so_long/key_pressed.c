/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:18:32 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/24 18:20:15 by josgarci         ###   ########.fr       */
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
	if (data->player.direction == 0)
	{
		if (keycode == key_s)
			go_left(data);
		if (keycode == key_w)
			go_right(data);
		if (keycode == key_d)
			go_down(data);
		if (keycode == key_a)
			go_up(data);
	}
	if (data->player.direction == 90)
	{
		if (keycode == key_a)
			go_left(data);
		if (keycode == key_d)
			go_right(data);
		if (keycode == key_s)
			go_down(data);
		if (keycode == key_w)
			go_up(data);
	}
	if (data->player.direction == 180)
	{
		if (keycode == key_w)
			go_left(data);
		if (keycode == key_s)
			go_right(data);
		if (keycode == key_a)
			go_down(data);
		if (keycode == key_d)
			go_up(data);
	}
	if (data->player.direction == 270)
	{
		if (keycode == key_d)
			go_left(data);
		if (keycode == key_a)
			go_right(data);
		if (keycode == key_w)
			go_down(data);
		if (keycode == key_s)
			go_up(data);
	}
/* 	if (keycode == 1 || keycode == 125)
		go_down(data);
	if (keycode == 13 || keycode == 126)
		go_up(data);
	if (keycode == 2)
		go_right(data);
	if (keycode == 0)
		go_left(data); */
	return (0);
}
