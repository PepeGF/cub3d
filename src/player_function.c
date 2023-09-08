#include "../inc/cub3d.h"

t_player	*where_is_the_player(t_board **board, int x, int y)
{
	int			i;
	int			j;
	t_player	*player;

	player = malloc(sizeof(t_player));
	*player = (t_player){}; //inicializar todo lo de player en 0 o NULL
	i = -1;
	while (++i < y)
	{
		j = 0;
		while (j < x)
		{
			if (is_player(board, i, j))
			{
				player->x = j + 0.5; //empieza en mitad de una cuadrícula
				player->y = i + 0.5;
				break ;
			}	
			j++;
		}
	}
	return (player);//hay que liberar esto
}

int	is_player(t_board **board, int i, int j)
{
	if (board[i][j].type == 'N' || board[i][j].type == 'S'
		|| board[i][j].type == 'E' || board[i][j].type == 'W')
		return (1);
	return (0);
}

void	set_player_initial_geometry(t_data *data, t_player *player)
{
	player->direction = ft_player_initial_direction(data->board, player);
	player->dir_rad = player->direction * (M_PI / 180);
	player->x_position = player->x * data->px + data->px / 2;
	player->y_position = player->y * data->px + data->px / 2;
	player->dir_x = cos(player->direction * 2 * M_PI / 360);
	player->dir_y = -1 * sin(player->direction * 2 * M_PI / 360);
	player->plane_x = 0.66 * cos(player->dir_rad + M_PI_2);
	player->plane_y = 0.66 * sin(player->dir_rad + M_PI_2);
}

int	ft_player_initial_direction(t_board **board, t_player *player)
{
	if (board[(int)player->y][(int)player->x].type == 'N')
	{
		player->dir_rad = M_PI_2;
		return (NORTH);
	}
	if (board[(int)player->y][(int)player->x].type == 'S')
	{
		player->dir_rad = 3 * M_PI_2;
		return (SOUTH);
	}
	if (board[(int)player->y][(int)player->x].type == 'W')
	{
		player->dir_rad = M_PI;
		return (WEST);
	}
	if (board[(int)player->y][(int)player->x].type == 'E')
	{
		player->dir_rad = 0;
		return (EAST);
	}
	else
		return (-1);	//en teoría es ha comprobado que hay player, por lo q devolver -1 es imposible
}
