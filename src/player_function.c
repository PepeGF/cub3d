#include "../inc/cub3d.h"

t_player	*where_is_the_player(t_board **board, int x, int y)
{
	int			i;
	int			j;
	t_player	*player;
// int k = 1;
	player = malloc(sizeof(t_player));

	*player = (t_player){}; //inicializar todo lo de player en 0 o NULL
	i = -1;
	while (++i < y)
	{
		j = 0;
		while (j < x)
		{
	// printf("Checking %d: %d\t%d\n",k, i, j);
			if (is_player(board, i, j))
			{
				// printf("Soy player, estoy en (%d,%d)\n", i, j);
				player->x = j;
				player->y = i;
				break ;
			}	
			j++;
			// k++;
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

void	ft_set_player_intial_geometry(t_data *data, t_player *player)
{
	player->direction = ft_player_initial_direction(data->board, *player);
	player->x_position = player->x * data->px + data->px / 2;
	player->y_position = player->y * data->px + data->px / 2;
	player->x_dir_vect = cos(player->direction * 2 * M_PI / 360);
	player->y_dir_vect = -1 * sin(player->direction * 2 * M_PI / 360);
}

int	ft_player_initial_direction(t_board **board, t_player player)
{
	if (board[player.y][player.x].type == 'N')
		return (90);
	if (board[player.y][player.x].type == 'S')
		return (270);
	if (board[player.y][player.x].type == 'W')
		return (180);
	if (board[player.y][player.x].type == 'E')
		return (0);
	else
		return (-1);	//en teoría es ha comprobado que hay player, por lo q devolver -1 es imposible
}
