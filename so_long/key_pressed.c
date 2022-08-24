/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:18:32 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/24 19:13:29 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	steps(t_data *data)
{
	print_steps(*data);
	printf("\rSteps: %d\n", data->mov_cont);
}

void	*choose_img(t_data *data)
{
	if (data->player.direction == NORTH)
		data->dino = mlx_xpm_file_to_image(data->mlx,
		"./img/arrow_90.xpm", &data->px, &data->px);
	else if (data->player.direction == EAST)
		data->dino = mlx_xpm_file_to_image(data->mlx,
		"./img/arrow_0.xpm", &data->px, &data->px);
	else if (data->player.direction == SOUTH)
		data->dino = mlx_xpm_file_to_image(data->mlx,
		"./img/arrow_270.xpm", &data->px, &data->px);
	else
		data->dino = mlx_xpm_file_to_image(data->mlx,
		"./img/arrow_180.xpm", &data->px, &data->px);
	return (data->dino);
}

void	turn_left(t_data *data)
{

	mlx_put_image_to_window(data->mlx, data->mlx_win, choose_img(data),
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
}

void	turn_right(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, choose_img(data),
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == key_esc || keycode == key_space || keycode == key_q)
		exit_game(data);
	if (keycode == key_left)
	{
		data->player.direction += 90;
		data->player.direction %= 360;
		printf("Nueva orientación %d\n", data->player.direction);
		turn_left(data);
	}
	if (keycode == key_right)
	{
		data->player.direction += 270;
		data->player.direction %= 360;
		printf("Nueva orientación %d\n", data->player.direction);
		turn_right(data);
	}
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
