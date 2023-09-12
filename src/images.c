#include "../inc/cub3d.h"

void	initialize_images(t_data *data)
{
	data->px = 64;
	// data->px = 16;
	data->mlx = mlx_init();
	data->field = mlx_xpm_file_to_image(data->mlx,
			"./img/gris.xpm", &data->px, &data->px);
	data->border = mlx_xpm_file_to_image(data->mlx,
			"./img/gris_copy.xpm", &data->px, &data->px);
	data->obs = mlx_xpm_file_to_image(data->mlx,
			"./img/gris_copy.xpm", &data->px, &data->px);
	// printf("COmprobación: %d\t%d\n", data->map_x_tot, data->map_y_tot);
	// data->mlx_win = mlx_new_window(data->mlx, data->px * data->map_x_tot,
	// 		data->px * data->map_y_tot, "cub3D");
	if (data->debug == true)
	{
		data->mlx_win = mlx_new_window(data->mlx, WIN_2D_WIDTH, WIN_2D_HEIGHT, "cub3D");
	}
	else //esto es vital, cuidado no quitar al limpiar
	{
		data->cub3d_image = malloc(sizeof(t_img));
		*(data->cub3d_image) = (t_img){};
		data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
		data->cub3d_image->img_data = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
		data->cub3d_image->buffer = (int *)mlx_get_data_addr(data->cub3d_image->img_data, &data->cub3d_image->bits_per_pixel, &data->cub3d_image->line_length, &data->cub3d_image->endian);
		data->cub3d_image->line_length /= 4;
	}
}