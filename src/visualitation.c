# include "../inc/cub3d.h"

void    visualize_no_texture(t_data *data, t_ray **ray)
{
	void    *image;
	int     pixel_bits;
	int     endian;
	int     *buffer;
	int     line_bytes;
	int     i;
	int     j;

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