#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;
// atexit(leakss);
(void)argv;
	list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc (sizeof(data));
	initialize_main_vars(data);
	list = ft_read_map(argv[1], data);//algunas cosas de esta no valen


	return (0);
}

void	initialize_main_vars(t_data *data)
{
	data->board = 0;
	data->cont = 0;
	data->map_x_tot = 0;
	data->map_y_tot = 0;
	data->mov_cont = 0;//no hace falta
	data->px = 16;
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (1);
	}
}
