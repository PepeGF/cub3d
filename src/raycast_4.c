/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:02:33 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 21:39:01 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel_img(t_img *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_from_tex_to_game(t_data *data, t_ray **ray, int i, int j)
{
	data->we->index = ray[i]->tex_y * data->we->line_length + ray[i]->tex_x
		* (data->we->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->we->addr[data->we->index + 2]) << 16)
		| ((unsigned char)(data->we->addr[data->we->index + 1]) << 8)
		| (unsigned char)(data->we->addr[data->we->index]);
	put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
}

void	set_ray_initial_values(t_ray **ray, int i, t_player *player)
{
	ray[i]->hit = false;
	ray[i]->camera_x = 2 * i / (double)WIN_WIDTH - 1;
	ray[i]->ray_dir_x = player->dir_x + player->plane_x
		* ray[i]->camera_x * -1;
	ray[i]->ray_dir_y = player->dir_y + player->plane_y
		* ray[i]->camera_x * -1;
	ray[i]->map_x = (int)player->x;
	ray[i]->map_y = (int)player->y;
	if (ray[i]->ray_dir_x == 0)
		ray[i]->delta_dist_x = 1e30;
	else
		ray[i]->delta_dist_x = fabs(1 / ray[i]->ray_dir_x);
	if (ray[i]->ray_dir_y == 0)
		ray[i]->delta_dist_y = 1e30;
	else
		ray[i]->delta_dist_y = fabs(1 / ray[i]->ray_dir_y);
}

void	set_ray_step_and_dist(t_ray **ray, int i, t_player *player)
{
	if (ray[i]->ray_dir_x < 0)
	{
		ray[i]->step_x = -1;
		ray[i]->side_dist_x = (player->x - ray[i]->map_x)
			* ray[i]->delta_dist_x;
	}
	else
	{
		ray[i]->step_x = 1;
		ray[i]->side_dist_x = (ray[i]->map_x + 1.0 - player->x)
			* ray[i]->delta_dist_x;
	}
	if (ray[i]->ray_dir_y < 0)
	{
		ray[i]->step_y = -1;
		ray[i]->side_dist_y = (player->y - ray[i]->map_y)
			* ray[i]->delta_dist_y;
	}
	else
	{
		ray[i]->step_y = 1;
		ray[i]->side_dist_y = (ray[i]->map_y + 1.0 - player->y)
			* ray[i]->delta_dist_y;
	}
}

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

void	calculates_for_textures(t_ray **ray, int i, t_player *player)
{
	if (ray[i]->face == 'w' || ray[i]->face == 'e')
		ray[i]->perp_wall_dist = ray[i]->side_dist_x - ray[i]->delta_dist_x;
	else
		ray[i]->perp_wall_dist = ray[i]->side_dist_y - ray[i]->delta_dist_y;
	ray[i]->line_height = (int)(WIN_HEIGHT / ray[i]->perp_wall_dist);
	if (ray[i]->line_height < 0)
		ray[i]->line_height = 62500;
	ray[i]->draw_start = WIN_HEIGHT / 2 - (ray[i]->line_height) / 2;
	if (ray[i]->draw_start < 0)
		ray[i]->draw_start = 0;
	ray[i]->draw_end = ray[i]->line_height / 2 + WIN_HEIGHT / 2;
	if (ray[i]->draw_end >= WIN_HEIGHT)
		ray[i]->draw_end = WIN_HEIGHT - 1;
	if (ray[i]->face == 'w' || ray[i]-> face == 'e')
		ray[i]->wall_x = player->y + ray[i]->perp_wall_dist
			* ray[i]->ray_dir_y;
	else
		ray[i]->wall_x = player->x + ray[i]->perp_wall_dist
			* ray[i]->ray_dir_x;
	ray[i]->wall_x -= floor(ray[i]->wall_x);
	ray[i]->tex_x = (int)(ray[i]->wall_x * (double)TEXTURE_WIDTH);
	if (ray[i]->face == 'w' || ray[i]->face == 'n')
		ray[i]->tex_x = TEXTURE_WIDTH - ray[i]->tex_x - 1;
}

void	get_north_color(t_ray **ray, int i, t_data *data)
{
	data->no->index = ray[i]->tex_y * data->no->line_length + ray[i]->tex_x
		* (data->no->bits_per_pixel / 8);
	ray[i]->color = ((unsigned char)(data->no->addr[data->no->index + 2]) << 16)
		| ((unsigned char)(data->no->addr[data->no->index + 1]) << 8)
		| (unsigned char)(data->no->addr[data->no->index]);
}

// void	get_south_color(t_ray **ray, int i, int j, t_data *data)
// {

// }

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
	{
		get_north_color(ray, i, data);
		// data->no->index = ray[i]->tex_y * data->no->line_length + ray[i]->tex_x * (data->no->bits_per_pixel / 8);
		// ray[i]->color = ((unsigned char)(data->no->addr[data->no->index + 2]) << 16) | ((unsigned char)(data->no->addr[data->no->index + 1]) << 8) | (unsigned char)(data->no->addr[data->no->index]);
	}
	else if (ray[i]->face == 's' && ray[i]->hit == true)
	{
		data->so->index = ray[i]->tex_y * data->so->line_length + ray[i]->tex_x * (data->so->bits_per_pixel / 8);
		ray[i]->color = ((unsigned char)(data->so->addr[data->so->index + 2]) << 16) | ((unsigned char)(data->so->addr[data->so->index + 1]) << 8) | (unsigned char)(data->so->addr[data->so->index]);
	}
	else if (ray[i]->face == 'e' && ray[i]->hit == true)
	{
		data->ea->index = ray[i]->tex_y * data->ea->line_length + ray[i]->tex_x * (data->ea->bits_per_pixel / 8);
		ray[i]->color = ((unsigned char)(data->ea->addr[data->ea->index + 2]) << 16) | ((unsigned char)(data->ea->addr[data->ea->index + 1]) << 8) | (unsigned char)(data->ea->addr[data->ea->index]);
	}
	else if (ray[i]->face == 'w' && ray[i]->hit == true)
	{
		data->we->index = ray[i]->tex_y * data->we->line_length + ray[i]->tex_x * (data->we->bits_per_pixel / 8);
		ray[i]->color = ((unsigned char)(data->we->addr[data->we->index + 2]) << 16) | ((unsigned char)(data->we->addr[data->we->index + 1]) << 8) | (unsigned char)(data->we->addr[data->we->index]);
	}
	put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
}

void	visualitation(t_ray **ray, int i, t_data *data)
{
	int	j;

	j = -1;
	while (++j < WIN_HEIGHT)
	{
		if (ray[i]->line_height > WIN_HEIGHT)
		{
			visualize_big_walls(ray, i, j, data);
		}
		if (j < ray[i]->draw_start && ray[i]->line_height <= WIN_HEIGHT)
			{
				put_pixel_img(data->cub3d_image, i, j, data->sky_color);
			}
		else if (j >= ray[i]->draw_start && j <= ray[i]->draw_end && ray[i]->line_height <= WIN_HEIGHT)
		{
			ray[i]->tex_y = (int)roundf((TEXTURE_HEIGHT - 1) * (j - ray[i]->draw_start) / ray[i]->line_height);
			// put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
			if (ray[i]->face == 'n' && ray[i]->hit == true)
			{
				data->no->index = ray[i]->tex_y * data->no->line_length + ray[i]->tex_x * (data->no->bits_per_pixel / 8);
				ray[i]->color = ((unsigned char)(data->no->addr[data->no->index + 2]) << 16) | ((unsigned char)(data->no->addr[data->no->index + 1]) << 8) | (unsigned char)(data->no->addr[data->no->index]);
				put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
			}
			else if (ray[i]->face == 's' && ray[i]->hit == true)
			{
				data->so->index = ray[i]->tex_y * data->so->line_length + ray[i]->tex_x * (data->so->bits_per_pixel / 8);
				ray[i]->color = ((unsigned char)(data->so->addr[data->so->index + 2]) << 16) | ((unsigned char)(data->so->addr[data->so->index + 1]) << 8) | (unsigned char)(data->so->addr[data->so->index]);
				put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
			}
			else if (ray[i]->face == 'e' && ray[i]->hit == true)
			{
				data->ea->index = ray[i]->tex_y * data->ea->line_length + ray[i]->tex_x * (data->ea->bits_per_pixel / 8);
				ray[i]->color = ((unsigned char)(data->ea->addr[data->ea->index + 2]) << 16) | ((unsigned char)(data->ea->addr[data->ea->index + 1]) << 8) | (unsigned char)(data->ea->addr[data->ea->index]);
				put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
			}
			else if (ray[i]->face == 'w' && ray[i]->hit == true)
			{
				data->we->index = ray[i]->tex_y * data->we->line_length + ray[i]->tex_x * (data->we->bits_per_pixel / 8);
				ray[i]->color = ((unsigned char)(data->we->addr[data->we->index + 2]) << 16) | ((unsigned char)(data->we->addr[data->we->index + 1]) << 8) | (unsigned char)(data->we->addr[data->we->index]);
				put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
			}
		}
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
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->cub3d_image->img_data, 0, 0);
}

t_ray	**initialize_ray(void)
{
	t_ray	**ray;
	int		i;

	i = 0;
	ray = malloc(sizeof(t_ray) * WIN_WIDTH);
	while (i < WIN_WIDTH)
	{
		ray[i] = malloc(sizeof(t_ray));
		*ray[i] = (t_ray){};
		i++;
	}
	return (ray); //hay que liberar esto
}