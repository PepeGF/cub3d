#include "../inc/cub3d.h"

void	ft_set_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		perror("Unable to create mlx pointer\n");
		exit(2);
	}
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (data->mlx_win == NULL)
	{
		perror("Unable to create window pointer\n");
		exit(2);
	}
	data->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_lenght), &(data->endian));
}

int main()
{
	// quiero conseguir encontrar cómo mantener una tecla pulsada
	t_data	data;

	data = (t_data){};
	ft_set_data(&data);
	
	printf("Mlx_ptr: %p\n", data.mlx_ptr);
	printf("Mlx_win: %p\n", data.mlx_win);
	printf("Mlx_img: %p\n", data.img);
	printf("Mlx_addr: %p\n", data.addr);
	printf("Mlx_bits_per_pixel: %d\n", data.bits_per_pixel);
	printf("Mlx_line_lenght: %d\n", data.line_lenght);
	printf("Mlx_endian: %d\n", data.endian);


	
	return 0;
}