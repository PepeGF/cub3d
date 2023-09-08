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
				player->x = j;
				player->y = i;
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
}

int	ft_player_initial_direction(t_board **board, t_player *player)
{
	if (board[player->y][player->x].type == 'N')
	{
		player->
		player->plane_x = -0.66;
		player->plane_y = 0;
		return (NORTH);
	}
	if (board[player->y][player->x].type == 'S')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
		return (SOUTH);
	}
	if (board[player->y][player->x].type == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
		return (WEST);
	}
	if (board[player->y][player->x].type == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0,66;
		return (EAST);
	}
	else
		return (-1);	//en teoría es ha comprobado que hay player, por lo q devolver -1 es imposible
}
