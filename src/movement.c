#include "../inc/cub3d.h"

void	turn(t_data *data, int keycode)
{
	data->player->turn_speed = TURN_SPEED;//ajusta la velocidad de giro
	if (keycode == key_right)
		data->player->turn_on = -1;
	else
		data->player->turn_on = 1;
	data->player->direction += data->player->turn_speed * data->player->turn_on;//establece nueva direccion
	data->player->direction %= 360;//quita vueltas si es necesario
	if (data->player->direction < 0)
		data->player->direction += 360;//lo convierte en angulo positivo, posiblemente innecesario, pero me gusta
	// printf("Direccion: %d\n", data->player->direction);
	draw_view_point(data);
	draw_full_map(data->board, data->map_y_tot, data->map_x_tot, data);
	raycast(data);
}

void	front_back(t_data *data, int keycode)
{
	double	player_pos_x_temp;
	double	player_pos_y_temp;

	draw_floor2d(data);//primero dibuja los 25 pixeles de suelo en la posición actual del jugador (borra el jugador)
	data->player->move_speed = MOVE_SPEED;//ajustar velocidad desplazamiento -> posible mejora, hacerla dependiente de las dimensiones del mapa??
	if (keycode == key_w || keycode == key_up)
		data->player->move_on = 1;
	else
		data->player->move_on = -1;
	//aquí faltaría el control de colisiones
	player_pos_x_temp = data->player->x_position + cos(data->player->direction * M_PI / 180) * data->player->move_speed * data->player->move_on;
	player_pos_y_temp = data->player->y_position + (-1 * sin(data->player->direction * M_PI / 180) * data->player->move_speed * data->player->move_on);
	get_future_pos_from_player_pixel(data, player_pos_x_temp, player_pos_y_temp);
	//habría que plantear si hay colisión no se mueve nada o se puede mover en paralelo al muro con el que colisiona
	if (check_x_collision(data, player_pos_x_temp) == 0)  //no hace falta else, si hay colisión x_position mantiene su valor, idem para los demás if de colisiones
		data->player->x_position = player_pos_x_temp;	//nueva posicion en x
	if (check_y_collision(data, player_pos_y_temp) == 0)
		data->player->y_position = player_pos_y_temp;//nueva posicion en y //el -1 de antes de sin es xq el sentido positivo de las y es hacia abajo
	set_current_grid(data);
	draw_full_map(data->board, data->map_y_tot, data->map_x_tot, data);
	draw_player(data);//dibuja al jugador en su nueva posicion
	raycast(data);
}

void	side_move(t_data *data, int keycode)
{
	double	player_pos_x_temp;
	double	player_pos_y_temp;

	draw_floor2d(data);//primero dibuja los 25 pixeles de suelo en la posición actual del jugador (borra el jugador)
	data->player->move_speed = MOVE_SPEED;//ajustar velocidad desplazamiento -> posible mejora, hacerla dependiente de las dimensiones del mapa??
	if (keycode == key_d)
		data->player->sideway_on = 1;
	else
		data->player->sideway_on = -1;
	player_pos_x_temp = data->player->x_position + cos(((data->player->direction + 270) % 360) * M_PI / 180) * data->player->move_speed * data->player->sideway_on;
	player_pos_y_temp = data->player->y_position + (-1 * sin(((data->player->direction + 270) % 360) * M_PI / 180) * data->player->move_speed * data->player->sideway_on);
	get_future_pos_from_player_pixel(data, player_pos_x_temp, player_pos_y_temp);
	if (check_x_collision(data, player_pos_x_temp) == 0)
		data->player->x_position = player_pos_x_temp;
	if (check_y_collision(data, player_pos_y_temp) == 0)
		data->player->y_position = player_pos_y_temp;
	set_current_grid(data);
	draw_full_map(data->board, data->map_y_tot, data->map_x_tot, data);
	draw_player(data);//dibuja al jugador en su nueva posicion
	raycast(data);
}

int get_future_pos_from_player_pixel(t_data *data, int player_pos_x_temp, int player_pos_y_temp)
{

	data->player->x_fut = player_pos_x_temp / data->px;
	data->player->y_fut = player_pos_y_temp / data->px;

	return (0);
}

int	check_x_collision(t_data *data, int	player_pos_x_temp)
{
	data->player->x_fut = player_pos_x_temp / data->px;
	data->player->y_fut = data->player->y_position / data->px;
	if (data->board[data->player->y_fut][data->player->x_fut].type == '1')
	{
		return (1);
	}
	else
		return (0);
}

int	check_y_collision(t_data *data, int	player_pos_y_temp)
{
	data->player->y_fut = player_pos_y_temp / data->px;
	data->player->x_fut = data->player->x_position / data->px;
	if (data->board[data->player->y_fut][data->player->x_fut].type == '1')
	{
		return (1);
	}
	return (0);
}

void	set_current_grid(t_data *data)
{
	data->player->x = data->player->x_position / data->px;
	data->player->y = data->player->y_position / data->px;
}

// printf("Nueva X: %f\tnueva y: %f\n", round(data->player->x_position), round(data->player->y_position));
// printf("Nueva X: %f\tnueva y: %f\n", round(data->player->x_position), round(data->player->y_position));
// printf("Cuadricula X: %d\tY: %d\n", data->player->x, data->player->y); //funciona bien

// printf("Me voy contra el muro en X\n");
// printf("Me voy contra el muro en Y\n");

// printf("Direccion: %d\n", data->player->direction);
