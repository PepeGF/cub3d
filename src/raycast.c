#include "../inc/cub3d.h"

t_ray	*initialize_ray(void)//temporal para tener todo inicializado
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	*ray = (t_ray){};
	/* 
		sirve para inicializar en 0 todas las variables de la estructura

	ray->ray_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->ray_direction = 0;
	ray->delta_angle = 0;
	ray->ray_up = 0;
	ray->ray_left = 0;
	ray->collision_x = 0;
	ray->collision_y = 0;
	ray->collision_x_h = 0;
	ray->collision_y_h = 0;
	ray->collision_x_v = 0;
	ray->collision_y_v = 0;
	ray->column = 0;
	ray->h_crash = false;
	ray->v_crash = false; 
	
	no borro todo esto por si me he pasado de listo*/

	return (ray); //hay que liberar esto
}

void	raycast(t_data *data)
{
	if (data->player->direction < 180 && data->player->direction != 0)
		data->ray->ray_up = 1;
	else if (data->player->direction > 180)
		data->ray->ray_up = -1;
	else
		data->ray->ray_up = 0;
	if (data->player->direction > 90 && data->player->direction < 270)
		data->ray->ray_left = 1;
	else if (data->player->direction == 90 || data->player->direction == 270)
		data->ray->ray_left = 0;
	else
		data->ray->ray_left = -1;
	calculate_first_ray_collision_horizontal(data);
	calculate_first_ray_collision_vertical(data);
	choose_closer_collision(data);
mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x, data->ray->collision_y, 0x000000);

}

int	distance_btw_points(int x_player, int y_player, int x_collision, int y_collision)
{
	int	distance;

	distance = sqrt((x_player - x_collision) * (x_player - x_collision) +
			(y_player - y_collision) * (y_player - y_collision));
	return (distance);
}

void	choose_closer_collision(t_data *data)
{
	data->ray->dist_h_collision = distance_btw_points(data->player->x_position,
		data->player->y_position, data->ray->collision_x_h, data->ray->collision_y_h);
	data->ray->dist_v_collision = distance_btw_points(data->player->x_position,
		data->player->y_position, data->ray->collision_x_v, data->ray->collision_y_v);
	if (data->ray->dist_h_collision <= data->ray->dist_v_collision)
	{
		data->ray->collision_x = data->ray->collision_x_h;
		data->ray->collision_y = data->ray->collision_y_h;
	}
	else
	{
		data->ray->collision_x = data->ray->collision_x_v;
		data->ray->collision_y = data->ray->collision_y_v;
	}
}

void	calculate_first_ray_collision_horizontal(t_data *data)
{
	data->ray->ray_direction = data->player->direction * M_PI / 180; //sumar o restar delta angulo * n (o -n)
	if (data->ray->ray_up == 1)
		data->ray->collision_y_h = data->player->y * data->px;
	else if (data->ray->ray_up == -1)
		data->ray->collision_y_h = (data->player->y + 1) * data->px;
	else
		data->ray->collision_y_h = data->player->y_position;
// printf("---------------------------------------\ntan(%d) = %f\n", data->player->direction, tan(data->ray->ray_direction));
// printf("Jugador px: (%f, %f)\n", data->player->x_position, data->player->y_position);
// printf("Jugador: (%d, %d)\n", data->player->x, data->player->y);
	/* if (data->ray->ray_up == 1) */
	data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	// else if (data->ray->ray_up == -1)
	// 	data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	// else
		// data->ray->collision_x_h = data->player->x_position;


/* ¡¡¡¡¡¡¡¡¡¡OJO LA TANGEENTE DE CERO HAY INT OVERFLOW!!!!!!!!!! */

	data->ray->h_crash = false;  //esto tengo que ponerlo en algún sitio y aun no tengo claro dónde

	calculate_ray_wall_collision_horizontal(data);
	// printf("Supuesta colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
}

void	calculate_first_ray_collision_vertical(t_data *data)
{
	data->ray->ray_direction = data->player->direction * M_PI / 180; //sumar o restar delta angulo * n (o -n)
	if (data->ray->ray_left == 1)
		data->ray->collision_x_v = data->player->x * data->px;
	else if (data->ray->ray_left == -1)
		data->ray->collision_x_v = (data->player->x + 1) * data->px;
	else
		data->ray->collision_x_v = data->player->x_position;
// printf("---------------------------------------\ntan(%d) = %f\n", data->player->direction, tan(data->ray->ray_direction));
// printf("Jugador px: (%f, %f)\n", data->player->x_position, data->player->y_position);
// printf("Jugador: (%d, %d)\n", data->player->x, data->player->y);
	/* if (data->ray->ray_up == 1) */
	data->ray->collision_y_v = data->player->y_position + (data->player->x_position - data->ray->collision_x_v) * tan(data->ray->ray_direction);
	// else if (data->ray->ray_up == -1)
	// 	data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	// else
		// data->ray->collision_x_h = data->player->x_position;


/* ¡¡¡¡¡¡¡¡¡¡OJO LA TANGEENTE DE CERO HAY INT OVERFLOW!!!!!!!!!! */

	data->ray->v_crash = false;  //esto tengo que ponerlo en algún sitio y aun no tengo claro dónde

	calculate_ray_wall_collision_vertical(data);
	// printf("Supuesta colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
}

void	calculate_ray_wall_collision_horizontal(t_data *data)
{
	data->ray->y_step = data->px;
	data->ray->x_step = data->ray->y_step / tan(data->ray->ray_direction + data->ray->delta_angle);// este cálculo no contempla dirección, solo es el valor absoluto
	if (data->ray->ray_up == 1)
	{
		data->ray->y_step *= -1;
		data->ray->collision_y_h -= 1;
	}
	if ((data->ray->ray_left == 1 && data->ray->x_step > 0) || (data->ray->ray_left == -1 && data->ray->x_step < 0))
		data->ray->x_step *= -1; //cambiar el signo de x_step si no es correcto
	while (!data->ray->h_crash)
	{ 
		data->ray->tile_x = data->ray->collision_x_h / data->px;
		data->ray->tile_y = data->ray->collision_y_h / data->px;
		// printf("Casilla colision: (%d, %d)\n", data->ray->tile_x, data->ray->tile_y);
		// printf("Pixel colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
		 
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
		{
			// printf("Se chocó contra mura horizontal\n");
			data->ray->h_crash = true;
			// break;
		}
		else
		{
			data->ray->collision_x_h += data->ray->x_step;
			data->ray->collision_y_h += data->ray->y_step;
			// printf("Despejado\n");
		}
	}
}

void	calculate_ray_wall_collision_vertical(t_data *data)
{
	data->ray->x_step = data->px;
	data->ray->y_step = data->ray->x_step * tan(data->ray->ray_direction + data->ray->delta_angle);// este cálculo no contempla dirección, solo es el valor absoluto
	if (data->ray->ray_left == 1)
	{
		data->ray->x_step *= -1;
		data->ray->collision_x_v -= 1;
	}
	if ((data->ray->ray_up == 1 && data->ray->y_step > 0) || (data->ray->ray_up == -1 && data->ray->y_step < 0))
		data->ray->y_step *= -1; //cambiar el signo de y_step si no es correcto
	// printf("Y step: %d\n", data->ray->y_step);
	data->ray->tile_x = data->ray->collision_x_v / data->px;
		data->ray->tile_y = data->ray->collision_y_v / data->px;
	// printf("Tile V crash: (%d, %d)\n", data->ray->tile_x, data->ray->tile_y);
	while (!data->ray->v_crash)
	{ 
		data->ray->tile_x = data->ray->collision_x_v / data->px;
		data->ray->tile_y = data->ray->collision_y_v / data->px;
		// printf("Casilla colision: (%d, %d)\n", data->ray->tile_x, data->ray->tile_y);
		// printf("Pixel colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
		 
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
		{
			// printf("Se chocó contra muro horizontal\n");
			data->ray->v_crash = true;
			// break;
		}
		else
		{
			data->ray->collision_x_v += data->ray->x_step;
			data->ray->collision_y_v += data->ray->y_step;
			// printf("Despejado\n");
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