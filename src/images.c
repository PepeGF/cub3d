#include "../inc/cub3d.h"

void	initialize_images(t_data *data)
{
	data->px = 16;
	data->mlx = mlx_init();
	data->field = mlx_xpm_file_to_image(data->mlx,
			"./img/gris.xpm", &data->px, &data->px);
	data->border = mlx_xpm_file_to_image(data->mlx,
			"./img/rojo.xpm", &data->px, &data->px);
	data->obs = mlx_xpm_file_to_image(data->mlx,
			"./img/rosa.xpm", &data->px, &data->px);
	// printf("COmprobación: %d\t%d\n", data->map_x_tot, data->map_y_tot);
	data->mlx_win = mlx_new_window(data->mlx, data->px * data->map_x_tot,
			data->px * data->map_y_tot, "cub3D");
}