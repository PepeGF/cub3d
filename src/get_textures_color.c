/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:54:43 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/24 09:55:24 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_north_color(t_ray **ray, int i, t_data *data)
{
	data->no->index = ray[i]->tex_y * data->no->line_length + ray[i]->tex_x
		* (data->no->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->no->addr[data->no->index + 2]) << 16)
		| ((unsigned char)(data->no->addr[data->no->index + 1]) << 8)
		| (unsigned char)(data->no->addr[data->no->index]);
}

void	get_south_color(t_ray **ray, int i, t_data *data)
{
	data->so->index = ray[i]->tex_y * data->so->line_length + ray[i]->tex_x
		* (data->so->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->so->addr[data->so->index + 2]) << 16)
		| ((unsigned char)(data->so->addr[data->so->index + 1]) << 8)
		| (unsigned char)(data->so->addr[data->so->index]);
}

void	get_east_color(t_ray **ray, int i, t_data *data)
{
	data->ea->index = ray[i]->tex_y * data->ea->line_length + ray[i]->tex_x
		* (data->ea->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->ea->addr[data->ea->index + 2]) << 16)
		| ((unsigned char)(data->ea->addr[data->ea->index + 1]) << 8)
		| (unsigned char)(data->ea->addr[data->ea->index]);
}

void	get_west_color(t_ray **ray, int i, t_data *data)
{
	data->we->index = ray[i]->tex_y * data->we->line_length + ray[i]->tex_x
		* (data->we->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->we->addr[data->we->index + 2]) << 16)
		| ((unsigned char)(data->we->addr[data->we->index + 1]) << 8)
		| (unsigned char)(data->we->addr[data->we->index]);
}
