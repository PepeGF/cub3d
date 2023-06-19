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


		//calcular primera colisión verticar
		calculate_first_ray_collision_horizontal(data);
		calculate_first_ray_collision_vertical(data);

		//iterar colisiones verticales
		//calcular distancia colision vertical

		//calcular primera colisión horizontal
		//iterar colisiones verticales
		//calcular distancia colision horizontal

		//elegir punto de menor distancia

		printf("%2d  (%3d,%3d)[%d,%d]\n",i, (int)round(data->ray->collision_x_h), (int)round(data->ray->collision_y_h), data->player->x, data->player->y);
		mlx_pixel_put(data->mlx, data->mlx_win, (int)data->ray->collision_x_h, (int)data->ray->collision_y_h, 0x000000);
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
	if (data->ray->ray_up == 0)
	{
		return ;
	}
}


void	calculate_first_ray_collision_vertical(t_data *data)
{
	(void)data;
}
// https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/