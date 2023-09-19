# include "../inc/cub3d.h"

void put_pixel_img(t_img game, int x, int y, int color)
{
	char	*dst;
	dst = game.addr + (y * game.line_length + x * (game.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	raycast(t_data *data, t_ray **ray, t_player *player)
{
	int	i;

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
				//esto es altamente probable que esté mal ----> REVISAR!!!!
				if (ray[i]->ray_dir_x > 0)
				{
					ray[i]->face = 'w';
					ray[i]->color = 0xFF0000;
				}
				else
				{
					ray[i]->face = 'e';
					ray[i]->color =0xfb85e8;
				}
			}
			else
			{
				ray[i]->side_dist_y += ray[i]->delta_dist_y;
				ray[i]->map_y += ray[i]->step_y;
				//esto es altamente probable que esté mal ----> REVISAR!!!!
				if (ray[i]->ray_dir_y > 0)
				{
					ray[i]->face = 's';
					ray[i]->color = 0xffa35e;
				}
				else
				{
					ray[i]->face = 'n';
					ray[i]->color = 0x85fb8c;
				}
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
		if (ray[i]->face == 'w' || ray[i]->face == 'n') //chequear esto si las imágenes salen al revés
			ray[i]->tex_x = TEXTURE_WIDTH - ray[i]->tex_x - 1;
		ray[i]->tex_step = (double)TEXTURE_HEIGHT / ray[i]->line_height;
		if (i == 500)
		{
			printf("Step: %f | step_wall: %f | line: %d\n", ray[i]->tex_step, 1/ray[i]->tex_step, ray[i]->line_height);
		}
		ray[i]->tex_pos = (ray[i]->draw_start - WIN_HEIGHT / 2 + ray[i]->line_height / 2) * ray[i]->tex_step;

		int j = -1;
		while (++j < WIN_HEIGHT)
		{
			if (j < ray[i]->draw_start)
				{
					// printf("%3d, %3d\t", i ,j); fflush(0);
					if (i == 500)
					{
						put_pixel_img(*(data->cub3d_image), i, j, 0xFF0000);
					}
					else
					put_pixel_img(*(data->cub3d_image), i, j, data->sky_color);
					// data->cub3d_image->buffer[(j * data->cub3d_image->line_length) + i] = data->sky_color;
				}
			else if (j >= ray[i]->draw_start && j <= ray[i]->draw_end)
			{
				ray[i]->tex_y = (int)roundf((TEXTURE_HEIGHT - 1) * (j - ray[i]->draw_start) / ray[i]->line_height);
				if (ray[i]->face == 'n' && ray[i]->hit == true)
				{
				// printf("Wololoooooooooo\t"); fflush(0);
					data->texture.no_img.index = ray[i]->tex_y * data->texture.no_img.line_length + ray[i]->tex_x * (data->texture.no_img.bits_per_pixel / 8);
					ray[i]->color = (data->texture.no_img.addr[data->texture.no_img.index + 2] << 16) | (data->texture.no_img.addr[data->texture.no_img.index + 1] << 8) | (data->texture.no_img.addr[data->texture.no_img.index]);
					// ray[i]->color = 0x880088;
					put_pixel_img(*(data->cub3d_image), i, j, ray[i]->color);

					// printf("%d\n", ray[i]->color);
				}
				else if (ray[i]->face == 's' && ray[i]->hit == true)
				{
					data->texture.so_img.index = ray[i]->tex_y * data->texture.so_img.line_length + ray[i]->tex_x * (data->texture.no_img.bits_per_pixel / 8);
					ray[i]->color = 0x440044;
					// ray[i]->color = ft_atoi(data->texture.so_img.addr + (ray[i]->tex_y * data->texture.so_img.line_length + ray[i]->tex_x * (data->texture.so_img.bits_per_pixel / 8)));
					put_pixel_img(*(data->cub3d_image), i, j, ray[i]->color);
				}
				else if (ray[i]->face == 'e' && ray[i]->hit == true)
				{
					data->texture.ea_img.index = ray[i]->tex_y * data->texture.ea_img.line_length + ray[i]->tex_x * (data->texture.no_img.bits_per_pixel / 8);
					ray[i]->color = 0x112233;
					put_pixel_img(*(data->cub3d_image), i, j, ray[i]->color);
					// ray[i]->color = ft_atoi(data->texture.ea_img.addr + (ray[i]->tex_y * data->texture.ea_img.line_length + ray[i]->tex_x * (data->texture.ea_img.bits_per_pixel / 8)));
				}
				else if (ray[i]->face == 'w' && ray[i]->hit == true)
				{
					data->texture.we_img.index = ray[i]->tex_y * data->texture.we_img.line_length + ray[i]->tex_x * (data->texture.no_img.bits_per_pixel / 8);
					ray[i]->color = 0x004444;
					put_pixel_img(*(data->cub3d_image), i, j, ray[i]->color);
					// ray[i]->color = ft_atoi(data->texture.we_img.addr + (ray[i]->tex_y * data->texture.we_img.line_length + ray[i]->tex_x * (data->texture.we_img.bits_per_pixel / 8)));
				}
				// data->cub3d_image->buffer[(j * data->cub3d_image->line_length) + i] = ray[i]->color;
				// if (i == 500)
				// {
				// 	printf("j: %3d | tex_y: %3d | cara: %c | color: %3d\t", j, ray[i]->tex_y, ray[i]->face, ray[i]->color);
				// 	fflush(0);
				// }
			}
			else
				put_pixel_img(*(data->cub3d_image), i, j, data->floor_color);
				// data->cub3d_image->buffer[(j * data->cub3d_image->line_length) + i] = data->floor_color;
		}
		i++;
	}
		printf("\n");
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