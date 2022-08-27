/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:01:10 by josgarci          #+#    #+#             */
/*   Updated: 2022/08/27 18:22:13 by josgarci         ###   ########.fr       */
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

	(void)data;
	return (0);
}

t_camera	*initialize_camera(void)//temporal para tener todo inicializado
{
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
	camera->camera_x = 0;
	camera->ray_dir_x = 0;
	camera->ray_dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0;
	return (camera); //hay que liberar esto
}

void	gt_get_camera_vector(t_data *data, t_player *player)
{
	//calcula vector positivo del plano de la cámara a partir del vector de vision del jugador
	
	data->camera->plane_x = player->y_dir_vect * 0.66 * (-1);
	data->camera->plane_y = player->x_dir_vect * 0.66;
	printf("vector camera: (%f,%f)\n", data->camera->plane_x, data->camera->plane_y);
	/* 
	N (0 ,-1) (0.66 , 0)
	S (0 , 1) (-0.66, 0)
	E (1 , 0) (0, 0.66)
	W (-1, 0) (0, -0.66)
	 */
}

void	raycast(t_data *data)
{
	(void)data;
}