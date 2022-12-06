#include "../inc/cub3d.h"

void	initialize_images(t_data *data)
{
/* 	char *initial_player_orientation;

	initial_player_orientation = ft_select_player_orientation(data); */
	data->px = 16;
	data->mlx = mlx_init();
	data->field = mlx_xpm_file_to_image(data->mlx,
			"./img/gris.xpm", &data->px, &data->px);
/* 	data->dino = mlx_xpm_file_to_image(data->mlx,
			initial_player_orientation, &data->px, &data->px); */
	// free(initial_player_orientation);
/* 	data->food = mlx_xpm_file_to_image(data->mlx,
			"./img/azul.xpm", &data->px, &data->px); */
	data->border = mlx_xpm_file_to_image(data->mlx,
			"./img/rojo.xpm", &data->px, &data->px);
	data->obs = mlx_xpm_file_to_image(data->mlx,
			"./img/rosa.xpm", &data->px, &data->px);
/* 	data->end = mlx_xpm_file_to_image(data->mlx,
	 		"./img/amarillo.xpm", &data->px, &data->px); */
	data->mlx_win = mlx_new_window(data->mlx, data->px * data->map_x_tot,//bien
			data->px * data->map_y_tot, "cub3D");//bien
}