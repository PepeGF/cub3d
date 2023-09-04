#include "../inc/cub3d.h"

void	raycast(t_data *data)
{
	(void)data;
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
	// 	calculate_ray(data, i);
		set_ray_basic(data, data->player, data->ray, i);
		calculate_first_ray_collision_horizontal(data, data->board, data->ray[i], data->player);
		calculate_first_ray_collision_vertical(data, data->board, data->ray[i], data->player);
//check_collision
	// 	calculate_first_ray_collision_vertical(data);
	// 	calculate_ray_collision_horizontal(data);
	// 	calculate_ray_collision_vertical(data);
	// 	calculate_ray_distance(data);
	// 	calculate_ray_height(data);
	// 	calculate_ray_texture(data);
	// 	draw_ray(data);
	mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray[i]->collision_x_h, (int)data->ray[i]->collision_y_h, 0x000000);
	mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray[i]->collision_x_v, (int)data->ray[i]->collision_y_v, 0xFF00FF);
		i++;
	}
	/* i = 0;
	for (i = 0; i < WIN_WIDTH; i++)
	{
		if (i % 10 == 0 && i != 0)
			printf("\n");
		printf("%f|up:%d|left%d\t", data->ray[i]->direction_deg, data->ray[i]->ray_up, data->ray[i]->ray_left);
	} */
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
	else if (ray->ray_left == 1)
	{
		ray->collision_y_h = player->y_position;
		ray->collision_x_h = (player->x_position >> 6) * data->px - 1;
	}
	else
	{
		ray->collision_y_h = player->y_position;
		ray->collision_x_h = (player->x_position >> 6) * data->px + data->px;
	}
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
	else if (ray->ray_up == 1)
	{
		ray->collision_x_v = player->x_position;
		ray->collision_y_v = (player->y_position >> 6) * data->px - 1;
	}
	else
	{
		ray->collision_x_v = player->x_position;
		ray->collision_y_v = (player->y_position >> 6) * data->px + data->px;
	}
}