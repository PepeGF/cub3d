/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:00:58 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/24 10:03:22 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel_img(t_img *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	return (ray);
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
