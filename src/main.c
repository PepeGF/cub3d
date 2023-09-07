#include "../inc/cub3d.h"

void	leaks()
{
	system("leaks cub3d -list -fullContent");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;
atexit(leaks);
	list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc(sizeof(t_data));//lo casteo xq visual no para de decirme q hay un error si no, pero no hace falta

	data->debug = false;

	initialize_main_vars(data);
	list = ft_read_map(argv[1], data);//algunas cosas de esta no valen
	data->board = ft_final_matrix(&list, data);
	//aquí iba data->cont, pero los contadores no van a hacer falta, así q pasando.
	data->ray = initialize_ray();
	data->player = where_is_the_player(data->board, data->map_x_tot, data->map_y_tot);//una vez me ha dado segfault, pero todas las variables están bien inicializadas, echar un ojo x si acaso
	initialize_images(data);
	set_player_initial_geometry(data, data->player);
	if (data->debug == true)
	{
		put_field(data->board, data->map_y_tot, data->map_x_tot, data);
		replace_field(data->board, data->map_y_tot, data->map_x_tot, data);
	}
	mlx_hook(data->mlx_win, 2, 0, &key_hook, data);// (1L << 17) captar pulsaciones mantenidas, investigar cómo evitar micropausa entre primera pulsacion y las demás
	mlx_hook(data->mlx_win, 17, 0, &exit_game, data); //(1L << 17) 
	mlx_loop(data->mlx);
	return (0);
}

void	initialize_main_vars(t_data *data)
{
	data->board = 0;
	data->map_x_tot = 0;
	data->map_y_tot = 0;
	data->px = 64;
	// data->px = 16;
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (1);
	}
} 


/* 
# include <stdio.h>
# include <mlx.h>
#include "../libft/libft.h"
# define width 640
# define heigth 360


int *ft_get_color_from_strings(char *array[2][3])
{
	int *colors;
	int	i;
	int	j;
	int	aux[2][3];

	colors = (int *)malloc(sizeof(int) * 2);
	i = 0;
	while(i < 2)
	{
		j = 0;
		while (j < 3)
		{
			aux[i][j] = ft_atoi(array[i][j]);
			j++;	
		}
		i++;
	}
	colors[0] = (aux[0][0] << 24) + (aux[0][1] << 16) + (aux[0][2] << 8);
	colors[1] = (aux[1][0] << 24) + (aux[1][1] << 16) + (aux[1][2] << 4);
	return colors;
}

void	leaks()
{
	system("leaks cub3D");
}


int main()
{
	atexit(leaks);
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, width, heigth, "Tutorial Window - Create Image");

	void *image = mlx_new_image(mlx, width, heigth);
	
	int pixel_bits;
	int line_bytes;
	int endian;
	int *buffer = (int *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	line_bytes /= 4;

	char *array[2][3] = {
		{"100", "0", "200"},
		{"10", "250", "30"}
	};
	int *colors;
	colors = ft_get_color_from_strings(array);
	
	int color = colors[0];
	for(int y = 0; y < heigth/2; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * line_bytes) + x] = color;
	}
	color = colors[1];
	for (int y = heigth/2; y < heigth; ++y)
	for(int x = 0; x < 640; ++x)
	{
		buffer[(y * line_bytes) + x] = color;
	}
	printf("pixel_bits: %d\nline_bytes: %d\nendia: %d\n", pixel_bits, line_bytes, endian);
	printf("floor: %d\nsky: %d\n", colors[0], colors[1]);

	mlx_put_image_to_window(mlx, win, image, 0, 0);
	free (colors);

	mlx_loop(mlx);
	return 0;
}
 */

/* int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, width, heigth, "Tutorial Window - Create Image");
​
	void *image = mlx_new_image(mlx, width, heigth);
	
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
​
	printf("pixel_bits: %d\nline_bytes: %d\nendia: %d\n", pixel_bits, line_bytes, endian);
	int color = 0xABCDEF;
​
printf("color antes: %d\n", color);
    color = mlx_get_color_value(mlx, color);
printf("color después: %d\n", color);
​
for(int y = 0; y < heigth/2; ++y)
for(int x = 0; x < 640; ++x)
{
    int pixel = (y * line_bytes) + (x * 4);
    //else if (endian == 0)   // Least significant (Blue) byte first
    
	buffer[pixel + 0] = (color) & 0xFF;
	buffer[pixel + 1] = (color >> 8) & 0xFF;
	buffer[pixel + 2] = (color >> 16) & 0xFF;
	buffer[pixel + 3] = (color >> 24);
    
}
color = 0x123456;
if (pixel_bits != 32)
    color = mlx_get_color_value(mlx, color);
​
for (int y = heigth/2; y < heigth; ++y)
for(int x = 0; x < 640; ++x)
{
	int pixel = (y * line_bytes) + (x * 4);
    //else if (endian == 0)   // Least significant (Blue) byte first
    
	buffer[pixel + 0] = (color) & 0xFF;
	buffer[pixel + 1] = (color >> 8) & 0xFF;
	buffer[pixel + 2] = (color >> 16) & 0xFF;
	buffer[pixel + 3] = (color >> 24);
}
​
	mlx_put_image_to_window(mlx, win, image, 0, 0);
	// The following code goes here.
​
	mlx_loop(mlx);
}
 */