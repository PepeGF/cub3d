/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:02:33 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/24 10:03:18 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_hits(t_ray **ray, int i, t_data *data)
{
	while (ray[i]->hit == false)
	{
		if (ray[i]->side_dist_x < ray[i]->side_dist_y)
		{
			ray[i]->side_dist_x += ray[i]->delta_dist_x;
			ray[i]->map_x += ray[i]->step_x;
			if (ray[i]->ray_dir_x > 0)
				ray[i]->face = 'e';
			else
				ray[i]->face = 'w';
		}
		else
		{
			ray[i]->side_dist_y += ray[i]->delta_dist_y;
			ray[i]->map_y += ray[i]->step_y;
			if (ray[i]->ray_dir_y > 0)
				ray[i]->face = 'n';
			else
				ray[i]->face = 's';
		}
		if (data->board[ray[i]->map_y][ray[i]->map_x].type == '1')
			ray[i]->hit = true;
	}
}

void	visualize_big_walls(t_ray **ray, int i, int j, t_data *data)
{
	ray[i]->tex_big_y_start = (TEXTURE_HEIGHT - 1) / 2
		* (1 - ray[i]->perp_wall_dist);
	ray[i]->tex_big_y_end = (TEXTURE_HEIGHT - 1)
		- ray[i]->tex_big_y_start;
	ray[i]->tex_y = (int)roundf(ray[i]->tex_big_y_start - 0.5
			+ ((ray[i]->tex_big_y_end - ray[i]->tex_big_y_start)
				* (double)j / (double)WIN_HEIGHT));
	if (ray[i]->face == 'n' && ray[i]->hit == true)
		get_north_color(ray, i, data);
	else if (ray[i]->face == 's' && ray[i]->hit == true)
		get_south_color(ray, i, data);
	else if (ray[i]->face == 'e' && ray[i]->hit == true)
		get_east_color(ray, i, data);
	else if (ray[i]->face == 'w' && ray[i]->hit == true)
		get_west_color(ray, i, data);
	put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
}

void	visalize_small_wall(t_ray **ray, int i, int j, t_data *data)
{
	ray[i]->tex_y = (int)roundf((TEXTURE_HEIGHT - 1)
			* (j - ray[i]->draw_start) / ray[i]->line_height);
	if (ray[i]->face == 'n' && ray[i]->hit == true)
		get_north_color(ray, i, data);
	else if (ray[i]->face == 's' && ray[i]->hit == true)
		get_south_color(ray, i, data);
	else if (ray[i]->face == 'e' && ray[i]->hit == true)
		get_east_color(ray, i, data);
	else if (ray[i]->face == 'w' && ray[i]->hit == true)
		get_west_color(ray, i, data);
	put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
}

void	visualitation(t_ray **ray, int i, t_data *data)
{
	int	j;

	j = -1;
	while (++j < WIN_HEIGHT)
	{
		if (ray[i]->line_height > WIN_HEIGHT)
			visualize_big_walls(ray, i, j, data);
		if (j < ray[i]->draw_start && ray[i]->line_height <= WIN_HEIGHT)
			put_pixel_img(data->cub3d_image, i, j, data->sky_color);
		else if (j >= ray[i]->draw_start && j <= ray[i]->draw_end
			&& ray[i]->line_height <= WIN_HEIGHT)
			visalize_small_wall(ray, i, j, data);
		else if (ray[i]->line_height <= WIN_HEIGHT)
			put_pixel_img(data->cub3d_image, i, j, data->floor_color);
	}
}

void	raycast(t_data *data, t_ray **ray, t_player *player)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		set_ray_initial_values(ray, i, player);
		set_ray_step_and_dist(ray, i, player);
		calculate_hits(ray, i, data);
		calculates_for_textures(ray, i, player);
		visualitation(ray, i, data);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->cub3d_image->img_data, 0, 0);
}
