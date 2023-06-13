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
	int	i;
int color;
	i = 1;
	data->ray->dist = (float *)malloc(sizeof(float) * WIN_WIDTH);
	while (i <= WIN_WIDTH)
	{	//										para empeza en la derecha		incrementa un delta de angulo
		data->ray->ray_direction = (float)((float)(data->player->direction) - (float)FOV / (float)2 + (float)(i - 1) * (float)FOV / (float)WIN_WIDTH);
		if (data->ray->ray_direction < 0)
			data->ray->ray_direction += 360;
		if (data->ray->ray_direction < 180 && data->ray->ray_direction != 0)
			data->ray->ray_up = 1;
		else if (data->ray->ray_direction > 180)
			data->ray->ray_up = -1;
		else
			data->ray->ray_up = 0;
		if (data->ray->ray_direction > 90 && data->ray->ray_direction < 270)
			data->ray->ray_left = 1;
		else if (data->ray->ray_direction == 90 || data->ray->ray_direction == 270)
			data->ray->ray_left = 0;
		else
			data->ray->ray_left = -1;
		data->ray->ray_direction = data->ray->ray_direction * M_PI / 180; //sumar o restar delta angulo * n (o -n)
		calculate_first_ray_collision_horizontal(data);
		calculate_first_ray_collision_vertical(data);
		choose_closer_collision(data, i);
		// printf("%d\t->  %d\t%9.6f\n", i, data->ray->dist[i], data->ray->ray_direction * 180 / M_PI);
		// if (i < 250 && i % 10 == 0)
		// 	color = 0x00ff00;
		// else if (i >= 250 && i % 10 == 0)
		// 	color = 0xff0000;
		// else if (i > 250)
		if (i > 245 && i < 255)
			color = 0x000000;
		else if (i < 245)
			color = 0xff0000;  //rojo menor de la mitad
		else
			color = 0xffffff; //blanco mayor de la mitad
		mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x, data->ray->collision_y, 0xff0000);
		printf("%3.d x:%3d y:%3d X:%3d Y:%3d\t", i, data->ray->collision_x, data->ray->collision_y, data->ray->tile_x, data->ray->tile_y);
		fflush(0);
		if (i%10 == 0)
			printf("\n");
		i++;
	}
}

float	distance_btw_points(int x_player, int y_player, int x_collision, int y_collision)
{
	float	distance;

	distance = sqrt((x_player - x_collision) * (x_player - x_collision) +
			(y_player - y_collision) * (y_player - y_collision));
	return (distance);
}

void	choose_closer_collision(t_data *data, int i)
{
	data->ray->dist_h_collision = distance_btw_points(data->player->x_position,
		data->player->y_position, data->ray->collision_x_h, data->ray->collision_y_h);
	data->ray->dist_v_collision = distance_btw_points(data->player->x_position,
		data->player->y_position, data->ray->collision_x_v, data->ray->collision_y_v);
	// if (i == 8)
	// mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x_h , data->ray->collision_y_h ,0x000000);
	// mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x_v , data->ray->collision_y_v ,0x222222);
	if (data->ray->dist_h_collision <= data->ray->dist_v_collision)
	{
		data->ray->collision_x = data->ray->collision_x_h;
		data->ray->collision_y = data->ray->collision_y_h;
		data->ray->dist[i] = data->ray->dist_h_collision;
	}
	else
	{
		data->ray->collision_x = data->ray->collision_x_v;
		data->ray->collision_y = data->ray->collision_y_v;
		data->ray->dist[i] = data->ray->dist_v_collision;
	}
		// printf("%3d h:%6.3f v:%6.3f d:%6.3f\t", i, data->ray->dist_h_collision, data->ray->dist_v_collision, data->ray->dist[i]);
// printf("%3d x:%3d h:%3d tx:%2d ty:%2d\t", i, data->ray->collision_x, data->ray->collision_y, data->ray->tile_x, data->ray->tile_y);
// fflush(0);
// if (i % 6 == 0 || i == 500)
// 	printf("\n");
}

void	calculate_first_ray_collision_horizontal(t_data *data)
{
	if (data->ray->ray_up == 1)
		data->ray->collision_y_h = data->player->y * data->px;
	else if (data->ray->ray_up == -1)
		data->ray->collision_y_h = (data->player->y + 1) * data->px;
	else
		data->ray->collision_y_h = data->player->y_position;
	data->ray->collision_x_h = data->player->x_position + (data->player->y_position - data->ray->collision_y_h) / tan(data->ray->ray_direction);
	data->ray->h_crash = false;  //esto tengo que ponerlo en algún sitio y aun no tengo claro dónde
	calculate_ray_wall_collision_horizontal(data);
	// printf("Supuesta colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
}

void	calculate_first_ray_collision_vertical(t_data *data)
{
	// data->ray->ray_direction = data->ray->ray_direction * M_PI / 180; //sumar o restar delta angulo * n (o -n)
	if (data->ray->ray_left == 1)
		data->ray->collision_x_v = data->player->x * data->px;
	else if (data->ray->ray_left == -1)
		data->ray->collision_x_v = (data->player->x + 1) * data->px;
	else
		data->ray->collision_x_v = data->player->x_position;

	data->ray->collision_y_v = data->player->y_position + (data->player->x_position - data->ray->collision_x_v) * tan(data->ray->ray_direction);
	data->ray->v_crash = false;  //esto tengo que ponerlo en algún sitio y aun no tengo claro dónde
	calculate_ray_wall_collision_vertical(data);
	// printf("Supuesta colision: (%d, %d)\n", data->ray->collision_x_h, data->ray->collision_y_h);
}

void	calculate_ray_wall_collision_horizontal(t_data *data)
{
	data->ray->y_step = data->px;
	data->ray->x_step = data->ray->y_step / tan(data->ray->ray_direction);// este cálculo no contempla dirección, solo es el valor absoluto
	if (data->ray->ray_up == 1)
	{
		data->ray->y_step *= -1;
		data->ray->collision_y_h -= 2;
	}
	if ((data->ray->ray_left == 1 && data->ray->x_step > 0) || (data->ray->ray_left == -1 && data->ray->x_step < 0))
		data->ray->x_step *= -1; //cambiar el signo de x_step si no es correcto
	while (!data->ray->h_crash)
	{
		// mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x_h, data->ray->collision_y_h, 0x0000ff);

		// data->ray->tile_x = (int)round((float)(data->ray->collision_x_h) / (float)data->px);
		// data->ray->tile_y = (int)round((float)(data->ray->collision_y_h) / (float)data->px);
		data->ray->tile_x = data->ray->collision_x_h / data->px;
		data->ray->tile_y = data->ray->collision_y_h / data->px;
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
		{
			data->ray->h_crash = true;
			break;
		}
		else if (corner_collision(data->board, data->ray->collision_x_h, data->ray->collision_y_h, data, 'h') == true)
		{
			data->ray->h_crash = true;
		}
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
	data->ray->y_step = data->ray->x_step * tan(data->ray->ray_direction);// este cálculo no contempla dirección, solo es el valor absoluto
	if (data->ray->ray_left == 1)
	{
		data->ray->x_step *= -1;
		data->ray->collision_x_v -= 2;
	}
	if ((data->ray->ray_up == 1 && data->ray->y_step > 0) || (data->ray->ray_up == -1 && data->ray->y_step < 0))
		data->ray->y_step *= -1; //cambiar el signo de y_step si no es correcto
	// data->ray->tile_x = data->ray->collision_x_v / data->px;
	// data->ray->tile_y = data->ray->collision_y_v / data->px;
	while (!data->ray->v_crash)
	{ 
		// mlx_pixel_put(data->mlx, data->mlx_win, data->ray->collision_x_v, data->ray->collision_y_v, 0x00ff00);
		// data->ray->tile_x = (int)round((float)(data->ray->collision_x_v) / (float)(data->px));
		// data->ray->tile_y = (int)round((float)(data->ray->collision_y_v) / (float)(data->px));
		data->ray->tile_x = data->ray->collision_x_v / data->px;
		data->ray->tile_y = data->ray->collision_y_v / data->px;
		if (collision(data->board, data->ray->tile_x, data->ray->tile_y, data) == true)
		{
			data->ray->v_crash = true;
			break;
		}
		// else if (corner_collision(data->board, data->ray->collision_x_v, data->ray->collision_y_v, data, 'v') == true)
		// {
		// 	data->ray->v_crash = true;
		// }
		else
		{
			data->ray->collision_x_v += data->ray->x_step;
			data->ray->collision_y_v += data->ray->y_step;
		}
	}
}

bool	corner_collision(t_board **board, int collision_x, int collision_y, t_data *data, char dir)
{
	int	aux_x;
	int	aux_y;

	aux_x = collision_x;
	aux_y = collision_y;
	if (dir == 'v')
	{
		if (data->ray->ray_left == 1)
			aux_x = collision_x + 1;
		else if (data->ray->ray_left == -1)
			aux_x = collision_x - 1;
	}
	else
	{
		if (data->ray->ray_up == 1)
			aux_y = collision_y + 1;
		else if (data->ray->ray_up == -1)
			aux_y = collision_y - 1;
		// if (collision(board, (int)(roundf((float)aux_x / (float)(data->px))), (int)roundf((float)aux_y / (float)(data->px)), data) == true)
	}
	if (collision(board, aux_x / data->px, aux_y / data->px, data) == true)
		return (true);
	else
		return (false);
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