#include "../inc/cub3d.h"

int	exit_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}