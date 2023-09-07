#include "../inc/cub3d.h"

void	raycast(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
	// 	calculate_ray(data, i);
		set_ray_basic(data, data->player, data->ray, i);
		calculate_first_ray_collision_horizontal(data, data->board, data->ray[i], data->player);
		calculate_first_ray_collision_vertical(data, data->board, data->ray[i], data->player);
		collision(data, data->board, data->player, data->ray[i]);
		calculate_ray_wall_collision_horizontal(data, data->board, data->player, data->ray[i]);
		calculate_ray_wall_collision_vertical(data, data->board, data->player, data->ray[i]);
		choose_closer_collision(data, data->player, data->ray[i]);
		calculate_face(data->ray[i]);
		calculate_wall_height(data, data->ray[i]);
		calculate_column(data, data->ray[i]);
		calculate_color(data->ray[i]); //solo para pruebas
	// 	calculate_ray_distance(data);
	// 	calculate_ray_texture(data);
	// 	draw_ray(data);
	if (data->debug == true)
	{
		if (data->ray[i]->chosen == 'v')
			mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray[i]->collision_x, (int)data->ray[i]->collision_y, 0x000000);
		else
			mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray[i]->collision_x, (int)data->ray[i]->collision_y, 0x000000);

	}
	// mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray[i]->collision_x_v, (int)data->ray[i]->collision_y_v, 0xFF00FF);
		i++;
	}
	if (data->debug == false)
		visualize_no_texture(data, data->ray);

	if (data->debug == true)
	{
		printf("\n");
		i = 0;
		for (i = 0; i < WIN_WIDTH; i++)
		{
			if (i % 3 == 0 && i != 0)
				printf("\n");
			// printf("%d|%.2f|up:%d|left%d|face:%c\t",i, data->ray[i]->direction_deg, data->ray[i]->ray_up, data->ray[i]->ray_left, data->ray[i]->face);
			// printf("%d|%.2f|Ad[-1]:%.2f|Ad[+1]:%.2f\t",i, data->ray[i]->dist, fabs(data->ray[i]->dist - data->ray[i - 1]->dist), fabs(data->ray[i]->dist - data->ray[i + 1]->dist));
			printf("%3d|%c|%3d|%3d|%3d\t",i, data->ray[i]->chosen, data->ray[i]->collision_x, data->ray[i]->collision_y, data->ray[i]->column);
		}
		printf("\n");
	}

	return ;
}

void	set_ray_up_right(t_ray **ray, int i)
{
	if (ray[i]->direction_deg > 0 && ray[i]->direction_deg < 180)
		ray[i]->ray_up = 1;
	else if (ray[i]->direction_deg > 180 && ray[i]->direction_deg < 360)
		ray[i]->ray_up = -1;
	else
		ray[i]->ray_up = 0;
	if (ray[i]->direction_deg > 90 && ray[i]->direction_deg < 270)
		ray[i]->ray_left = 1;
	else if (ray[i]->direction_deg == 90 || ray[i]->direction_deg == 270)
		ray[i]->ray_left = 0;
	else
		ray[i]->ray_left = -1;
}

void	set_ray_basic(t_data *data, t_player *player, t_ray **ray, int i)
{(void)data;
	ray[i]->direction_deg = player->direction + (float)FOV / 2 - i
		* (float)FOV / (float)WIN_WIDTH;
	if (ray[i]->direction_deg < 0)
			ray[i]->direction_deg += 360;
	if (ray[i]->direction_deg >= 360)
		ray[i]->direction_deg -= 360;
	ray[i]->direction_rad = ray[i]->direction_deg * M_PI / 180;
	set_ray_up_right(ray, i);
	return ;
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

void	calculate_first_ray_collision_horizontal(t_data *data, t_board **board,
		t_ray *ray, t_player *player)
{
	(void)board;
	if (ray->ray_up == 1)
	{
		ray->collision_y_h = (player->y_position >> 6) * data->px - 1;
		ray->collision_x_h = player->x_position	+ (player->y_position
			- ray->collision_y_h) / tan(ray->direction_rad);
	}
	else if (ray->ray_up == -1)
	{
		ray->collision_y_h = (player->y_position >> 6) * data->px + data->px;
		ray->collision_x_h = player->x_position + (player->y_position
			- ray->collision_y_h) / tan(ray->direction_rad);
	}
	/* else if (ray->ray_left == 1)
	{
		ray->collision_y_h = player->y_position;
		ray->collision_x_h = (player->x_position >> 6) * data->px - 1;
	}
	else
	{
		ray->collision_y_h = player->y_position;
		ray->collision_x_h = (player->x_position >> 6) * data->px + data->px;
	} */
}

void	calculate_first_ray_collision_vertical(t_data *data, t_board **board,
		t_ray *ray, t_player *player)
{
	(void)board;
	if (ray->ray_left == 1)
	{
		ray->collision_x_v = (player->x_position >> 6) * data->px - 1;
		ray->collision_y_v = player->y_position + (player->x_position
			- ray->collision_x_v) * tan(ray->direction_rad);
	}
	else if (ray->ray_left == -1)
	{
		ray->collision_x_v = (player->x_position >> 6) * data->px + data->px;
		ray->collision_y_v = player->y_position + (player->x_position
			- ray->collision_x_v) * tan(ray->direction_rad);
	}
	/* else if (ray->ray_up == 1)
	{
		ray->collision_x_v = player->x_position;
		ray->collision_y_v = (player->y_position >> 6) * data->px - 1;
	}
	else
	{
		ray->collision_x_v = player->x_position;
		ray->collision_y_v = (player->y_position >> 6) * data->px + data->px;
	} */
}

void	adjust_tiles(t_ray *ray, t_data *data)
{
	if (ray->tile_x < 0)
		ray->tile_x = 0;
	if (ray->tile_y < 0)
		ray->tile_y = 0;
	if (ray->tile_x > data->map_x_tot - 1)
		ray->tile_x = data->map_x_tot - 1;
	if (ray->tile_y > data->map_y_tot - 1)
		ray->tile_y = data->map_y_tot - 1;
}

void	collision(t_data *data, t_board **board, t_player *player, t_ray *ray)
{
	(void)data;
	(void)player;
	ray->tile_x = ray->collision_x_h >> 6;
	ray->tile_y = ray->collision_y_h >> 6;
	adjust_tiles(ray, data);
	if (board[ray->tile_y][ray->tile_x].type == '1')
		ray->h_crash = true;
	else
		ray->h_crash = false;
	ray->tile_x = ray->collision_x_v >> 6;
	ray->tile_y = ray->collision_y_v >> 6;
	adjust_tiles(ray, data);
	if (board[ray->tile_y][ray->tile_x].type == '1')
		ray->v_crash = true;
	else
		ray->v_crash = false;
}

void	calculate_ray_wall_collision_horizontal(t_data *data, t_board **board,
		t_player *player, t_ray *ray)
{
	(void)player;
	if (ray->h_crash == false)
	{
		ray->y_step = data->px;
		ray->x_step = fabs(data->px / tan(ray->direction_rad));
		if (ray->ray_up == 1 && ray->ray_left == 1)
		{
			ray->y_step *= -1;
			ray->x_step *= -1;
		}
		else if (ray->ray_up == 1 && ray->ray_left == -1)
			ray->y_step *= -1;
		else if (ray->ray_up == -1 && ray->ray_left == 1)
			ray->x_step *= -1;
		while (ray->h_crash == false)
		{
			ray->tile_x = ray->collision_x_h >> 6;
			ray->tile_y = ray->collision_y_h >> 6;
			adjust_tiles(ray, data);
			if (board[ray->tile_y][ray->tile_x].type == '1')
				ray->h_crash = true;
			else
			{
				ray->collision_x_h += ray->x_step;
				ray->collision_y_h += ray->y_step;
			}
		}
	}
}

void	calculate_ray_wall_collision_vertical(t_data *data, t_board **board,
		t_player *player, t_ray *ray)
{
	(void)player;
	(void)board;
	(void)data;
	if (ray->v_crash == false)
	{
		ray->x_step = data->px;
		ray->y_step = fabs(data->px * tan(ray->direction_rad));
		if (ray->ray_up == 1 && ray->ray_left == 1)
		{
			ray->y_step *= -1;
			ray->x_step *= -1;
		}
		else if (ray->ray_up == 1 && ray->ray_left == -1)
			ray->y_step *= -1;
		else if (ray->ray_up == -1 && ray->ray_left == 1)
			ray->x_step *= -1;
	}
		while (ray->v_crash == false)
		{
			ray->tile_x = ray->collision_x_v >> 6;
			ray->tile_y = ray->collision_y_v >> 6;
			adjust_tiles(ray, data);
			if (board[ray->tile_y][ray->tile_x].type == '1')
				ray->v_crash = true;
			else
			{
				ray->collision_x_v += ray->x_step;
				ray->collision_y_v += ray->y_step;
			}
	}
}

void	choose_closer_collision(t_data *data, t_player *player, t_ray *ray)
{
	(void)data;
	ray->dist_h_collision = sqrt(pow(player->x_position - ray->collision_x_h, 2)
			+ pow(player->y_position - ray->collision_y_h, 2));
	ray->dist_v_collision = sqrt(pow(player->x_position - ray->collision_x_v, 2)
			+ pow(player->y_position - ray->collision_y_v, 2));
	if (ray->dist_h_collision < ray->dist_v_collision)
	{
		ray->collision_x = ray->collision_x_h;
		ray->collision_y = ray->collision_y_h;
		ray->dist = ray->dist_h_collision;
		ray->chosen = 'h';
	}
	else
	{
		ray->collision_x = ray->collision_x_v;
		ray->collision_y = ray->collision_y_v;
		ray->dist = ray->dist_v_collision;
		ray->chosen = 'v';
	}
}

void	calculate_face(t_ray *ray)
{
	if (ray->chosen == 'v' && ray->ray_left == 1)
		ray->face = 'e';
	else if (ray->chosen == 'v')
		ray->face = 'w';
	else if (ray->ray_up == 1)
		ray->face = 's';
	else
		ray->face = 'n';
}

void	calculate_wall_height(t_data *data, t_ray *ray)
{
	ray->wall_height = (data->px / ray->dist) * 277; //277 es la distancia al plano de proyección
	//creo que falta multiplicar por el coseno de ray->direction_rad
	ray->wall_height *= cos(ray->direction_rad - data->player->direction * M_PI / 180);
	ray->draw_start = - ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;

}
 
void	calculate_column(t_data *data, t_ray *ray)
{
	if (ray->chosen == 'h' && ray->ray_left == 1)
	{
		ray->column = data->px - ray->collision_x % data->px;
	}
	else if (ray->ray_left == -1)
	{
		ray->column = ray->collision_x % data->px;
	}
	else if (ray->chosen == 'v' && ray->ray_up == 1)
	{
		ray->column = ray->collision_y % data->px;
	}
	else
	{
		ray->column = data->px - ray->collision_y % data->px;
	}
}

void	calculate_color(t_ray *ray)
{
	if (ray->face == 'e')
		ray->color = 0xFF0000;
	if (ray->face == 'w')
		ray->color = 0xFF0000 / 2;
	if (ray->face == 's')
		ray->color = 0x00FF00;
	if (ray->face == 'n')
		ray->color = 0x00FF00 / 2;
}




