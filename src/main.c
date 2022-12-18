#include "../inc/cub3d.h"

int32_t	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;
	mlx_image_t *image;
// atexit(leakss);
	// list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc(sizeof(t_data));//lo casteo xq visual no para de decirme q hay un error si no, pero no hace falta
	initialize_main_vars(data);
	list = ft_read_map(argv[1], data);//algunas cosas de esta no valen
	data->board = ft_final_matrix(&list, data);
	data->ray = initialize_ray();
	data->player = where_is_the_player(data->board, data->map_x_tot, data->map_y_tot);//una vez me ha dado segfault, pero todas las variables están bien inicializadas, echar un ojo x si acaso

	image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);

	


	return (EXIT_SUCCESS);
}



void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (1);
	}
}

void	initialize_main_vars(t_data *data)
{
	if (!data)
		exit(1); //protección del malloc hecho en main
	*data = (t_data){};
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", true);
	// data->board = 0;
	// data->cont = 0;
	// data->map_x_tot = 0;
	// data->map_y_tot = 0;
	// data->mov_cont = 0;//no hace falta
	data->px = 16;
}