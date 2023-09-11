# include "../inc/cub3d.h"

void	init_texture(t_data *data)
{
	data->texture.no_path = "./img/NO.xpm";
	data->texture.so_path = "./img/SO.xpm";
	data->texture.we_path = "./img/WE.xpm";
	data->texture.ea_path = "./img/EA.xpm";

	data->texture.no_img.img_data = mlx_xpm_file_to_image(data->mlx, data->texture.no_path, &data->texture.no_img.width, &data->texture.no_img.height);
	data->texture.so_img.img_data = mlx_xpm_file_to_image(data->mlx, data->texture.so_path, &data->texture.so_img.width, &data->texture.so_img.height);
	data->texture.we_img.img_data = mlx_xpm_file_to_image(data->mlx, data->texture.we_path, &data->texture.we_img.width, &data->texture.we_img.height);
	data->texture.ea_img.img_data = mlx_xpm_file_to_image(data->mlx, data->texture.ea_path, &data->texture.ea_img.width, &data->texture.ea_img.height);

	data->texture.no_img.addr = mlx_get_data_addr(data->texture.no_img.img_data, &data->texture.no_img.bits_per_pixel, &data->texture.no_img.line_length, &data->texture.no_img.endian);
	data->texture.so_img.addr = mlx_get_data_addr(data->texture.so_img.img_data, &data->texture.so_img.bits_per_pixel, &data->texture.so_img.line_length, &data->texture.so_img.endian);
	data->texture.we_img.addr = mlx_get_data_addr(data->texture.we_img.img_data, &data->texture.we_img.bits_per_pixel, &data->texture.we_img.line_length, &data->texture.we_img.endian);
	data->texture.ea_img.addr = mlx_get_data_addr(data->texture.ea_img.img_data, &data->texture.ea_img.bits_per_pixel, &data->texture.ea_img.line_length, &data->texture.ea_img.endian);
}

void	visualize_with_texture(t_data *data, t_ray ** ray)
{
	init_texture(data);
	
	int buffer[WIN_HEIGHT][WIN_WIDTH];
	(void)buffer;
	
	(void)data;
	(void)ray;
}


void	visualize_no_texture(t_data *data, t_ray **ray)
{
	visualize_with_texture(data, ray);
	void	*image;
	int		pixel_bits;
	int		endian;
	int		*buffer;
	int		line_bytes;
	int		i;
	int		j;

	image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	buffer = (int *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	line_bytes /= 4;
	data->sky_color = 0xABCDEF;
	data->floor_color = 0x123456;
// printf("line_bytes = %d\npixel_bits: %d\n", line_bytes, pixel_bits);
	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			if (j < ray[i]->draw_start)
				buffer[(j * line_bytes) + i] = data->sky_color;
			else if (j >= ray[i]->draw_start && j <= ray[i]->draw_end)
				buffer[(j * line_bytes) + i] = ray[i]->color;
			else
				buffer[(j * line_bytes) + i] = data->floor_color;
				// printf("%d|%d\t", i, j);
				// fflush(0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, image, 0, 0);
	mlx_destroy_image(data->mlx, image);
	return ;
}