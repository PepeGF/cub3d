#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;
// atexit(leakss);
	list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc(sizeof(t_data));//lo casteo xq visual no para de decirme q hay un error si no, pero no hace falta
	initialize_main_vars(data);
	list = ft_read_map(argv[1], data);//algunas cosas de esta no valen
	data->board = ft_final_matrix(&list, data);
	//aquí iba data->cont, pero los contadores no van a hacer falta, así q pasando.
	data->ray = initialize_ray();
	data->player = where_is_the_player(data->board, data->map_x_tot, data->map_y_tot);//una vez me ha dado segfault, pero todas las variables están bien inicializadas, echar un ojo x si acaso
	initialize_images(data);
	set_player_initial_geometry(data, data->player);
	put_field(data->board, data->map_y_tot, data->map_x_tot, data);
	replace_field(data->board, data->map_y_tot, data->map_x_tot, data);
	mlx_hook(data->mlx_win, 2, 0/* (1L << 17) */, &key_hook, data);//captar pulsaciones mantenidas, investigar cómo evitar micropausa entre primera pulsacion y las demás
	mlx_hook(data->mlx_win, 17, 0/* (1L << 17) */, &exit_game, data);
	mlx_loop(data->mlx);
	return (0);
}

void	initialize_main_vars(t_data *data)
{
	data->board = 0;
	// data->cont = 0;
	data->map_x_tot = 0;
	data->map_y_tot = 0;
	data->mov_cont = 0;//no hace falta
	data->px = 32;
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

