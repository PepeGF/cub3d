/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:57 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/30 19:13:00 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* void	end_game(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->player.x += x;
	data->player.y += y;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->dino,
		(data->board[data->player.x][data->player.y].col * data->px),
		(data->board[data->player.x][data->player.y].row * data->px));
	data->mov_cont += 1;
	// steps(data);
	exit (0);
} */

void	turn(t_data *data, int keycode)
{
	data->player.turn_speed = 5;//ajusta la velocidad de giro
	if (keycode == key_right)
		data->player.turn_on = -1;
	else
		data->player.turn_on = 1;
	data->player.direction += data->player.turn_speed * data->player.turn_on;//establece nueva direccion
	// printf("%d, %d, %d\n", data->player.direction, data->player.turn_speed, data->player.turn_on);
	data->player.direction %= 360;//quita vueltas si es necesario
	if (data->player.direction < 0)
		data->player.direction += 360;//lo convierte en angulo positivo, posiblemente innecesario, pero me gusta
	printf("Direccion: %d\n", data->player.direction);
}

void	front_back(t_data *data, int keycode)
{
	draw_floor2d(*data);//primero dibuja los 25 pixeles de suelo en la posición actual del jugador (borra el jugador)
	data->player.move_speed = 3;//ajustar velocidad desplazamiento -> posible mejora, hacerla dependiente de las dimensiones del mapa??
	if (keycode == key_w || keycode == key_up)
		data->player.turn_on = 1;
	else
		data->player.turn_on = -1;
	//aquí faltaría el control de colisiones
	//habría que plantear si hay colisión no se mueve nada o se puede mover en paralelo al muro con el que colisiona
	data->player.x_position += (cos(data->player.direction * M_PI / 180) * data->player.move_speed * data->player.turn_on);	//nueva posicion en x
	data->player.y_position += (-1 * sin(data->player.direction * M_PI / 180) * data->player.move_speed * data->player.turn_on);//nueva posicion en y //el -1 de antes de sin es xq el sentido positivo de las y es hacia abajo
	printf("Nueva X: %f\tnueva y: %f\n", round(data->player.x_position), round(data->player.y_position));
	draw_player(*data);//dibuja al jugador en su nueva posicion
}

void	side_move(t_data *data, int keycode)
{
	if (keycode == key_d)
		data->player.sideway_on = 1;
	else
		data->player.sideway_on = -1;
	//creo que tengo q cambiar cos por sin en x e y, pero no tengo claro que sea tan sencillo

}

void	move_player(t_data *data, int y, int x)//creo que ya no se usa para nada, no la comento del todo x si acaso
{	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->field,
		(data->board[data->player.y][data->player.x].col * data->px),
		(data->board[data->player.y][data->player.x].row * data->px));
	data->player.x += x;
	data->player.y += y;
	draw_player(*data);
	// mlx_put_image_to_window(data->mlx, data->mlx_win, data->dino,
	// 	(data->board[data->player.y][data->player.x].col * data->px),
	// 	(data->board[data->player.y][data->player.x].row * data->px));
	data->mov_cont += 1;
	// ft_get_player_position(&data->player, *data);
	// printf("Nueva posición: x: %d\ty: %d\n", data->player.x_position, data->player.y_position);
	// steps(data);
}

void	check_if_colleccionable(t_data *data)
{
	if (data->board[data->player.x][data->player.y].type == 'C')
	{
		data->cont->coll -= 1;
		data->board[data->player.x][data->player.y].type = '0';
	}
}
