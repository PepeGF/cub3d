/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:01:10 by josgarci          #+#    #+#             */
/*   Updated: 2022/12/06 10:47:13 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_calculate_distance_to_wall(t_data *data)
{
	// calcular posición del jugador medida en pixeles
		// añadir a la estructura 2 variables para almacenar esto
		// vector posicion == x e y en pixeles
	// para el rayo central se puede calcular siguiendo la dirección
	 //del jugador hasta que encuentre un 1, pero es poco útil
	// cada rayo dista un 1 pixel del central o el anterior.
	// dependiendo del tamaño de la ventana el angulo de cada rayo variará
	// no
	// hay que definir el plano de proyección y su distancia al jugador...no?
	
	// el ángulo de cada rayo es angulo_de_vision(90º?)/resolución_horizontal_ventana
	/* int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		data->ray->ray_x = 2 * x / double(WIN_WIDTH) - 1;
		data->ray->ray_dir_x = data->player.x_dir_vect + data->ray->ray_x;
		data->ray->ray_dir_y = data->player.y_dir_vect + data->ray->ray_y;
		x++;
	} */
	(void)data;
	return (0);
}

t_ray	*initialize_ray(void)//temporal para tener todo inicializado
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->ray_direction = 0;
	ray->delta_angle = 0;
	ray->ray_up = 0;
	ray->ray_left = 0;
	ray->collision_x = 0;
	ray->collision_y = 0;
	ray->collision_x_h = 0;
	ray->collision_y_h = 0;
	ray->collision_x_v = 0;
	ray->collision_y_v = 0;
	ray->column = 0;
	ray->h_crash = false;
	ray->v_crash = false;
	return (ray); //hay que liberar esto
}

void	raycast(t_data *data)
{
// calcular la interseccion del rayo central
	// calcular intersecciones horizontales
	// calcular intersecciones verticales
		// comparar ambas intersecciones
		// elegir el más cercano
		// dibujar el rayo (bresenham)

	if (data->player.direction < 180 && data->player.direction != 0)
		data->ray->ray_up = 1;
	else if (data->player.direction > 180)
		data->ray->ray_up = -1;
	else
		data->ray->ray_up = 0;
	if (data->player.direction > 90 && data->player.direction < 270)
		data->ray->ray_left = 1;
	else if (data->player.direction == 90 || data->player.direction == 270)
		data->ray->ray_left = 0;
	else
		data->ray->ray_left = -1;
	// printf("Rayo arriba: %d\t\t\tRayo izq: %d\n", data->ray->ray_up, data->ray->ray_left);
	calculate_first_ray_collision_horizontal(data);
}

void	calculate_first_ray_collision_horizontal(t_data *data)
{
	data->ray->ray_direction = data->player.direction * M_PI / 180;
	if (data->ray->ray_up == 1)
		data->ray->collision_y_h = data->player.y * data->px;
	else if (data->ray->ray_up == -1)
		data->ray->collision_y_h = (data->player.y + 1) * data->px;
	else
		data->ray->collision_y_h = data->player.y_position;
	if (data->ray->ray_up == 1)
		data->ray->collision_x_h = data->player.x_position + (data->player.y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	else if (data->ray->ray_up == -1)
		data->ray->collision_x_h = data->player.x_position - (data->player.y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	else
		data->ray->collision_x_h = 1000000;
	// printf("%f\n", tan(data->ray->ray_direction));
	printf("Coord primera inter horiz:\nx: %d\ty: %d\n\
	-----------------------------------------------\n", data->ray->collision_x_h, data->ray->collision_y_h);
	calculate_ray_wall_collision_horizontal(data);
}

void	calculate_ray_wall_collision_horizontal(t_data *data)
{
	data->ray->y_step = data->px;
	data->ray->x_step = data->ray->y_step / tan(data->ray->ray_direction + data->ray->delta_angle);// este cálculo no contempla dirección, solo es el valor absoluto
	if (data->ray->ray_up == 1)
		data->ray->y_step *= -1;
	if ((data->ray->ray_left == 1 && data->ray->x_step > 0) || (data->ray->ray_left == -1 && data->ray->x_step < 0))
		data->ray->x_step *= -1; //cambiar el signo de x_step si no es correcto
	if (data->ray->ray_up)
		data->ray->collision_y_h -= 1;

	/* while (!data->ray->h_crash)
	{ */
		data->ray->tile_x = data->ray->collision_x_h / data->px;
		data->ray->tile_y = data->ray->collision_y_h / data->px;
		printf("Casilla X colision: %d\n", data->ray->tile_x);
		printf("Casilla Y colision: %d\n", data->ray->tile_y);
		/* 
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y) == true)
		{
			printf("Se chocó contra mura horizontal\n");
			data->ray->h_crash = true;
		}
		else
		{
			printf("Despejado\n");
			break;
		} */
	// }
}

bool	collision(t_board **board, int tile_x, int tile_y)
{
	if (board[tile_x][tile_y].is_border == 1)
		return (true);
	else
		return (false);
}