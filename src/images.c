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
		// *(data->cub3d_image) = (t_img){};
		data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
		data->cub3d_image->img_data = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
		data->cub3d_image->addr = mlx_get_data_addr(data->cub3d_image->img_data, &data->cub3d_image->bits_per_pixel, &data->cub3d_image->line_length, &data->cub3d_image->endian);
		// data->cub3d_image->line_length /= 4;
		data->sky_color = 0xABCDEF;
		data->floor_color = 0x123456;
		init_texture(data);

		// printf("Imagen CUB3D inicializada. sky_color:%x | floor_color:%x\n", data->sky_color, data->floor_color);
	}
}

void	init_texture(t_data *data)
{
	data->no = (t_img *)malloc(sizeof(t_img));
	data->so = (t_img *)malloc(sizeof(t_img));
	data->ea = (t_img *)malloc(sizeof(t_img));
	data->we = (t_img *)malloc(sizeof(t_img));

	data->no->path = ft_strdup("./img/NO.xpm"); //Esto tiene que venir del parseo del mapa
	data->so->path = ft_strdup("./img/SO.xpm");
	data->ea->path = ft_strdup("./img/EA.xpm");
	data->we->path = ft_strdup("./img/WE.xpm");

	data->no->img_data = mlx_xpm_file_to_image(data->mlx, data->no->path, &(data->no->width), &(data->no->height));
	data->so->img_data = mlx_xpm_file_to_image(data->mlx, data->so->path, &(data->so->width), &(data->so->height));
	data->ea->img_data = mlx_xpm_file_to_image(data->mlx, data->ea->path, &(data->ea->width), &(data->ea->height));
	data->we->img_data = mlx_xpm_file_to_image(data->mlx, data->we->path, &(data->we->width), &(data->we->height));

	// printf("NO: %s | w: %d | h: %d\n", data->no->path, data->no->width, data->no->height);
	// printf("SO: %s | w: %d | h: %d\n", data->so->path, data->so->width, data->so->height);
	// printf("EA: %s | w: %d | h: %d\n", data->ea->path, data->ea->width, data->ea->height);
	// printf("WE: %s | w: %d | h: %d\n", data->we->path, data->we->width, data->we->height);

	data->no->addr = mlx_get_data_addr(data->no->img_data, &(data->no->bits_per_pixel), &(data->no->line_length), &(data->no->endian));
	data->so->addr = mlx_get_data_addr(data->so->img_data, &(data->so->bits_per_pixel), &(data->so->line_length), &(data->so->endian));
	data->ea->addr = mlx_get_data_addr(data->ea->img_data, &(data->ea->bits_per_pixel), &(data->ea->line_length), &(data->ea->endian));
	data->we->addr = mlx_get_data_addr(data->we->img_data, &(data->we->bits_per_pixel), &(data->we->line_length), &(data->we->endian));

	// printf("NO: %p | ll: %d | addr: %s\n", data->no->img_data, data->no->line_length, data->no->addr);
	// printf("SO: %p | ll: %d | addr: %s\n", data->so->img_data, data->so->line_length, data->so->addr);
	// printf("EA: %p | ll: %d | addr: %s\n", data->ea->img_data, data->ea->line_length, data->ea->addr);
	// printf("WE: %p | ll: %d | addr: %s\n", data->we->img_data, data->we->line_length, data->we->addr);
	
}