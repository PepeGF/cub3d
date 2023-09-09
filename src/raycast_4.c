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
		if (ray[i]->ray_dir_x == 0)
			ray[i]->delta_dist_x = 1e30;
		else
			ray[i]->delta_dist_x = fabs(1 / ray[i]->side_dist_x);
		if (ray[i]->ray_dir_y == 0)
			ray[i]->delta_dist_y = 1e30;
		else
			ray[i]->delta_dist_y = fabs(1 / ray[i]->side_dist_y);
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
		while (ray[i]->hit == false)
		{
			if (ray[i]->side_dist_x < ray[i]->side_dist_y)
			{
				ray[i]->side_dist_x += ray[i]->delta_dist_x;
				ray[i]->map_x += ray[i]->step_x;
				//esto es altamente probable que esté mal ----> REVISAR!!!!
				if (ray[i]->ray_dir_x > 0)
					ray[i]->face = 'w';
				else
					ray[i]->face = 'e';
				
			}
			else
			{
				ray[i]->side_dist_y += ray[i]->delta_dist_y;
				ray[i]->map_y += ray[i]->step_y;
				//esto es altamente probable que esté mal ----> REVISAR!!!!
				if (ray[i]->ray_dir_y > 0)
					ray[i]->face = 's';
				else
					ray[i]->face = 'n';
			}
			if (data->board[ray[i]->map_x][ray[i]->map_y].type == '1')
				ray[i]->hit = true;
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
		ray[i]->line_height = (int)(i / ray[i]->perp_wall_dist);
		ray[i]->draw_start = -(ray[i]->line_height) / 2 + WIN_HEIGHT / 2;
		if (ray[i]->draw_start < 0)
			ray[i]->draw_start = 0;
		ray[i]->draw_end = ray[i]->line_height / 2 + WIN_HEIGHT / 2;
		if (ray[i]->draw_end >= WIN_HEIGHT)
			ray[i]->draw_end = WIN_HEIGHT - 1;
		i++;
	}

	//comprobaciones para debug
	if (data->debug == false)
	i = 0;
	{
		while (i < WIN_WIDTH)
		{
			printf("Rayo: %3d | %f, %f\n", i, ray[i]->ray_dir_x, ray[i]->ray_dir_y);
			i++;
		}
	}
	if (data->debug == false)
		printf("Playerr: %f, %f, %f | %f, %f, %f\n", player->dir_x, player->dir_y, 
			sqrt(pow(player->dir_x, 2)+pow(player->dir_y, 2)), player->plane_x, player->plane_y,
			sqrt(pow(player->plane_x, 2)+pow(player->plane_y, 2)));
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