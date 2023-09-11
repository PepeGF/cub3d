# include "../inc/cub3d.h"

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
		ray[i]->line_height = (int)(WIN_WIDTH / ray[i]->perp_wall_dist);
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
		ray[i]->tex_step = 1.0 * TEXTURE_HEIGHT / ray[i]->line_height;
		ray[i]->tex_pos = (ray[i]->draw_start - WIN_HEIGHT / 2 + ray[i]->line_height / 2) * ray[i]->tex_step;

		while(ray[i]->y < ray[i]->draw_end)
		{
			ray[i]->tex_y = (int)ray[i]->tex_pos & (TEXTURE_HEIGHT - 1);
			ray[i]->tex_pos += ray[i]->tex_step;

			//terminar de hacer las texturas
			
			//buffer[tex_y][i] = texture[4][tex_y][tex_x];
			(ray[i]->y)++;
		}




		i++;
	}
/* 
	if (data->debug == true)
			printf("\n");
	//comprobaciones para debug
	if (data->debug == true)
	i = 0;
	{
		while (i < WIN_WIDTH)
		{
			printf("Rayo: %3d | %f | %c\n", i, ray[i]->perp_wall_dist, ray[i]->face);
			// printf("Rayo: %3d | %f, %f\n", i, ray[i]->ray_dir_x, ray[i]->ray_dir_y);
			i++;
		}
	}
	if (data->debug == true)
		printf("Playerr: %f, %f, %f | %f, %f, %f\n", player->dir_x, player->dir_y, 
			sqrt(pow(player->dir_x, 2)+pow(player->dir_y, 2)), player->plane_x, player->plane_y,
			sqrt(pow(player->plane_x, 2)+pow(player->plane_y, 2)));
	 */
	if (data->debug == false)
		visualize_no_texture(data, ray);
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