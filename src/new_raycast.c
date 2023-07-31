#include "../inc/cub3d.h"

t_ray	*initialize_ray(void)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	*ray = (t_ray){};
	return (ray); //hay que liberar esto
}

void	raycast(t_data *data)
{
	int	i;
	i = 0;
	printf("player:(%3d, %3d)\n", data->player->x_position, data->player->y_position);
	while (i <= WIN_WIDTH)
	{
		data->ray->direction_deg = data->player->direction - (float)FOV / 2 + i * ((float)FOV / (float)WIN_WIDTH);
		if (data->ray->direction_deg < 0)
			data->ray->direction_deg += 360;
		if (data->ray->direction_deg >= 360)
			data->ray->direction_deg -= 360;
		data->ray->direction_rad = (float)data->ray->direction_deg * M_PI / 180;

		//establecer condiciones de direcciones
		if (data->ray->direction_deg > 0 && data->ray->direction_deg < 180)
			data->ray->ray_up = 1;
		else if (data->ray->direction_deg == 0 || data->ray->direction_deg == 180)
			data->ray->ray_up = 0;
		else
			data->ray->ray_up = -1;
		if (data->ray->direction_deg > 90 && data->ray->direction_deg < 270)
			data->ray->ray_left = 1;
		else if (data->ray->direction_deg == 90 || data->ray->direction_deg == 270)
			data->ray->ray_left = 0;
		else
			data->ray->ray_left = -1;


		//calcular primera colisión horizontal
		calculate_first_ray_collision_horizontal(data);
		//calcular primera colisión verticar
		calculate_first_ray_collision_vertical(data);

		//iterar colisiones horizontales
		calculate_ray_wall_collision_horizontal(data);
		//iterar colisiones verticales
		calculate_ray_wall_collision_vertical(data);
		//calcular distancia colision horizontal
		//calcular distancia colision vertical

		//elegir punto de menor distancia


		printf("%2d  (%3d,%3d)[%d,%d]\n",i, (int)round(data->ray->collision_x_h), (int)round(data->ray->collision_y_h), data->player->x, data->player->y);
		mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray->collision_x_h, (int)data->ray->collision_y_h, 0x000000);
		mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray->collision_x_v, (int)data->ray->collision_y_v, 0xff00ff);
		if (i == WIN_WIDTH)
			printf("\n");
		i++;
	}

}

void	calculate_first_ray_collision_horizontal(t_data *data)
{
	//si va para arriba
	if (data->ray->ray_up == 1)
	{
		data->ray->collision_y_h = (data->player->y_position / data->px) * data->px - 1;
		data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->direction_rad);
		// return ;
	} 
	//si va para abajo
	if (data->ray->ray_up == -1)
	{
		data->ray->collision_y_h = (data->player->y_position / data->px) * data->px + data->px;
		data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->direction_rad);
		// return ;
	}
	//si no sube ni baja
	// if (data->ray->ray_up == 0)
	// {
	// 	return ;
	// }
	data->ray->h_crash = false;
}


void	calculate_first_ray_collision_vertical(t_data *data)
{
	if (data->ray->ray_left == 1)
	{
		data->ray->collision_x_v = (data->player->x_position / data->px) * data->px - 1;
		data->ray->collision_y_v = data->player->y_position + (data->player->x_position - data->ray->collision_x_v) * tan(data->ray->direction_rad);
	}
	if (data->ray->ray_left == -1)
	{
		data->ray->collision_x_v = (data->player->x_position / data->px) * data->px + data->px;
		data->ray->collision_y_v = data->player->y_position + (data->player->x_position - data->ray->collision_x_v) * tan(data->ray->direction_rad);
	}
	// if (data->ray->ray_left == 0)
	// {
	// 	return ;
	// }
	data->ray->v_crash = false;
}

void	calculate_ray_wall_collision_horizontal(t_data *data)
{
	data->ray->y_step = data->px;
	data->ray->x_step = fabs(data->px / tan(data->ray->direction_rad));
	//si va para arriba
	if (data->ray->ray_up == 1 && data->ray->ray_left == 1)
	{
		data->ray->y_step *= -1;
		data->ray->x_step *= -1;
	}
	if (data->ray->ray_up == 1 && data->ray->ray_left == -1)
		data->ray->y_step *= -1;
	//si va para abajo
	if (data->ray->ray_up == -1 && data->ray->ray_left == 1)
		data->ray->x_step *= -1;

	while (data->ray->h_crash == false)
	{
		data->ray->tile_x = (int)(data->ray->collision_x_h / data->px);
		data->ray->tile_y = (int)(data->ray->collision_y_h / data->px);
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
			data->ray->h_crash = true;
		else
		{
			data->ray->collision_x_h += data->ray->x_step;
			data->ray->collision_y_h += data->ray->y_step;
		}
	}
}

void	calculate_ray_wall_collision_vertical(t_data *data)
{
	data->ray->x_step = data->px;
	data->ray->y_step = fabs(data->px * tan(data->ray->direction_rad));
	//si va para la izquierda
	if (data->ray->ray_left == 1 && data->ray->ray_up == 1)
	{
		data->ray->y_step *= -1;
		data->ray->x_step *= -1;
	}
	if (data->ray->ray_left == 1 && data->ray->ray_up == -1)
		data->ray->x_step *= -1;
	//si va para la derecha
	if (data->ray->ray_left == -1 && data->ray->ray_up == 1)
		data->ray->y_step *= -1;

	while (data->ray->v_crash == false)
	{
		data->ray->tile_x = (int)(data->ray->collision_x_v / data->px);
		data->ray->tile_y = (int)(data->ray->collision_y_v / data->px);
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
		{	
			data->ray->v_crash = true;
			printf("Casilla : (%d, %d)\n", data->ray->tile_x, data->ray->tile_y);
		}
		else
		{
			data->ray->collision_x_v += data->ray->x_step;
			data->ray->collision_y_v += data->ray->y_step;
		}
	}
}


bool	collision(t_board **board, int tile_x, int tile_y, t_data *data)
{
	// if (tile_x < 0 || tile_y < 0)
	// 	return (true);
	// printf("Casilla : (%d, %d)\n", tile_x, tile_y);
	if (tile_x < 0 || tile_x > data->map_x_tot - 1 || tile_y < 0 || tile_y > data->map_y_tot - 1)
		return (true);
	if (board[tile_y][tile_x].type == '1')
		return (true);
	else
		return (false);
}


// https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/