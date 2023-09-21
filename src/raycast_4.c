# include "../inc/cub3d.h"

void put_pixel_img(t_img *game, int x, int y, int color)
{
	char	*dst;
	// dst = game->img_data + (y * game->line_length + x * (game->bits_per_pixel / 8));
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	// printf("color:%d\n", color);
	*(unsigned int *)dst = color;
}

void	raycast(t_data *data, t_ray **ray, t_player *player)
{
	int	i;
// printf("Direccion memoria: %p || %s\n", data->cub3d_image->addr, data->cub3d_image->addr);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray[i]->hit = false;
		ray[i]->camera_x = 2 * i / (double)WIN_WIDTH - 1;
		ray[i]->ray_dir_x = player->dir_x + player->plane_x * ray[i]->camera_x * -1;
		ray[i]->ray_dir_y = player->dir_y + player->plane_y * ray[i]->camera_x * -1;
		ray[i]->map_x = (int)player->x;
		ray[i]->map_y = (int)player->y;
		if (data->debug == true)
		{
			printf("Antes: %d, %d || ", ray[i]->map_x, ray[i]->map_y);
			fflush(0);
		}
		//calculate step and initial sideDist
		if (ray[i]->ray_dir_x == 0)
			ray[i]->delta_dist_x = 1e30;
		else
			ray[i]->delta_dist_x = fabs(1 / ray[i]->ray_dir_x);
		if (ray[i]->ray_dir_y == 0)
			ray[i]->delta_dist_y = 1e30;
		else
			ray[i]->delta_dist_y = fabs(1 / ray[i]->ray_dir_y);
		
		if (data->debug == true)
		{
			printf("Rayo: %3d | %f, %f | %f, %f\n", i, ray[i]->delta_dist_x, ray[i]->delta_dist_y,
				ray[i]->ray_dir_x, ray[i]->ray_dir_y);
			fflush(0);
		}

		//calculate step and initial sideDist
		if (ray[i]->ray_dir_x < 0)
		{
			ray[i]->step_x = -1;
			ray[i]->side_dist_x = (player->x - ray[i]->map_x) * ray[i]->delta_dist_x;
		}
		else
		{
			ray[i]->step_x = 1;
			ray[i]->side_dist_x = (ray[i]->map_x + 1.0 - player->x) * ray[i]->delta_dist_x;
		}
		if (ray[i]->ray_dir_y < 0)
		{
			ray[i]->step_y = -1;
			ray[i]->side_dist_y = (player->y - ray[i]->map_y) * ray[i]->delta_dist_y;
		}
		else
		{
			ray[i]->step_y = 1;
			ray[i]->side_dist_y = (ray[i]->map_y + 1.0 - player->y) * ray[i]->delta_dist_y;
		}
		if (data->debug == true)
		{
			printf("Rayo: %3d | %f, %f | %f, %f | %f, %f\n", i, ray[i]->delta_dist_x, ray[i]->delta_dist_y,
				ray[i]->ray_dir_x, ray[i]->ray_dir_y, ray[i]->side_dist_x, ray[i]->side_dist_y);
			fflush(0);
			if (i == WIN_WIDTH - 1)
				printf("\n");
		}
//hasta aquí parece estar bien

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
			if ((i % 10 == 0 || i == WIN_WIDTH - 1) && data->debug == true)
			{
				printf("Rayo: %3d:  %d , %d\n", i, ray[i]->map_x, ray[i]->map_y);
			}
		}
		if (data->debug == true)
		{
			printf("Después: %d, %d\n", ray[i]->map_x, ray[i]->map_y);
			fflush(0);
		}
		if (ray[i]->face == 'w' || ray[i]->face == 'e')
			ray[i]->perp_wall_dist = ray[i]->side_dist_x - ray[i]->delta_dist_x;
		else
			ray[i]->perp_wall_dist = ray[i]->side_dist_y - ray[i]->delta_dist_y;
		ray[i]->line_height = (int)(WIN_HEIGHT / ray[i]->perp_wall_dist);
		ray[i]->draw_start = WIN_HEIGHT / 2 - (ray[i]->line_height) / 2;
		if (ray[i]->draw_start < 0)
			ray[i]->draw_start = 0;
		ray[i]->draw_end = ray[i]->line_height / 2 + WIN_HEIGHT / 2;
		if (ray[i]->draw_end >= WIN_HEIGHT)
			ray[i]->draw_end = WIN_HEIGHT - 1;

		//texturas
		if (ray[i]->face == 'w' || ray[i]-> face == 'e')
			ray[i]->wall_x = player->y + ray[i]->perp_wall_dist * ray[i]->ray_dir_y;
		else
			ray[i]->wall_x = player->x + ray[i]->perp_wall_dist * ray[i]->ray_dir_x;
		ray[i]->wall_x -= floor(ray[i]->wall_x);
		ray[i]->tex_x = (int)(ray[i]->wall_x * (double)TEXTURE_WIDTH);
		if (ray[i]->face == 'w' || ray[i]->face == 'n')
			ray[i]->tex_x = TEXTURE_WIDTH - ray[i]->tex_x - 1;

		int j = -1;
		while (++j < WIN_HEIGHT)
		{
			if (j < ray[i]->draw_start)
				{
					put_pixel_img(data->cub3d_image, i, j, data->sky_color);
				}
			else if (j >= ray[i]->draw_start && j <= ray[i]->draw_end)
			{
				ray[i]->tex_y = (int)roundf((TEXTURE_HEIGHT - 1) * (j - ray[i]->draw_start) / ray[i]->line_height);
				put_pixel_img(data->cub3d_image, i, j, ray[i]->color);
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
			else
				put_pixel_img(data->cub3d_image, i, j, data->floor_color);
		}
		i++;
	}
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->cub3d_image->img_data, 0, 0);
		// mlx_destroy_image(data->mlx, data->cub3d_image->img_data);
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