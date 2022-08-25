/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:01:10 by josgarci          #+#    #+#             */
/*   Updated: 2022/08/25 20:30:22 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_calculate_distance_to_wall(t_data *data)
{
	// calcular posición del jugador medida en pixeles
		// añadir a la estructura 2 variables para almacenar esto
		// vector posicion == x e y en pixeles
	// para el rayo central se puede calcular siguiento la dirección
	 //del jugador hasta que encuentre un 1, pero es poco útil
	// cada rayo dista un 1 pixel del central o el anterior.
	// dependiendo del tamaño de la ventana el angulo de cada rayo variará
	// no
	// hay que definir el plano de proyección y su distancia al jugador...no?
	
	// el ángulo de cada rayo es angulo_de_vision(90º?)/resolución_horizontal_ventana
	

	(void)data;
	return (0);
}