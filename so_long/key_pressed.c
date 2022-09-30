/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:18:32 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/30 19:03:59 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	steps(t_data *data)
{
	print_steps(*data);
	printf("\rSteps: %d\n", data->mov_cont);
}
/* 
void	*choose_img(t_data *data)	//esta tanpoco va a valer
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
} */
/* 
void	turn_left(t_data *data)
{

	mlx_put_image_to_window(data->mlx, data->mlx_win, choose_img(data),
		(data->board[data->player.y][data->player.x].col * data->px),
		(data->board[data->player.y][data->player.x].row * data->px));
}

void	turn_right(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, choose_img(data),
		(data->board[data->player.y][data->player.x].col * data->px),
		(data->board[data->player.y][data->player.x].row * data->px));
}
 */
int	key_hook(int keycode, t_data *data)
{
	if (keycode == key_esc || keycode == key_space || keycode == key_q)
		exit_game(data);

	if (keycode == key_left || keycode == key_right)
		turn(data, keycode);

	if (keycode == key_w || keycode == key_s || keycode == key_up || keycode == key_down)
		front_back(data, keycode);
	
	if (keycode == key_a || keycode == key_d)
		side_move(data, keycode);
/* 
	if (keycode == key_left)
	{
		data->player.direction += 90;
		data->player.direction %= 360;
		turn_left(data);
		ft_get_player_dir_vector(&data->player, *data);
	}
	if (keycode == key_right)
	{
		data->player.direction += 270;
		data->player.direction %= 360;
		turn_right(data);
		ft_get_player_dir_vector(&data->player, *data);
	}
 */	
/* //esto servía para movimientos de 90º, ahora hay que calcular la direccion
	//cada vez dependiendo de la dirección a la que mira el jugador	
	if (data->player.direction == 0)
	{
		if (keycode == key_s || keycode == key_down)
			go_left(data);
		if (keycode == key_w || keycode == key_up)
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
		if (keycode == key_s || keycode == key_down)
			go_down(data);
		if (keycode == key_w || keycode == key_up)
			go_up(data);
	}
	if (data->player.direction == 180)
	{
		if (keycode == key_w || keycode == key_up)
			go_left(data);
		if (keycode == key_s || keycode == key_down)
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
		if (keycode == key_w || keycode == key_up)
			go_down(data);
		if (keycode == key_s || keycode == key_down)
			go_up(data);
	}
 */
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
