#include "../inc/cub3d.h"

int32_t	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;
// atexit(leakss);
	list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc(sizeof(t_data));//lo casteo xq visual no para de decirme q hay un error si no, pero no hace falta
	initialize_main_vars(data);


	data = 0;
	(void)argv;
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
	*data = (t_data){};
	// data->board = 0;
	// data->cont = 0;
	// data->map_x_tot = 0;
	// data->map_y_tot = 0;
	// data->mov_cont = 0;//no hace falta
	data->px = 16;
}