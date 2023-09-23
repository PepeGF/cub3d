/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:30:48 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 19:37:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d -list -fullContent");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_list	*list;

	list = 0;
	ft_check_argc(argc);
	data = (t_data *)malloc(sizeof(t_data));
	data->debug = false;
	initialize_main_vars(data);
	list = ft_read_map(argv[1], data);
	data->board = ft_final_matrix(&list, data);
	data->ray = initialize_ray();
	data->player = where_is_the_player(data->board, data->map_x_tot,
			data->map_y_tot);
	initialize_images(data);
	set_player_initial_geometry(data, data->player);
	raycast(data, data->ray, data->player);
	mlx_hook(data->mlx_win, 2, 0, &key_hook, data);
	mlx_hook(data->mlx_win, 17, 0, &exit_game, data);
	mlx_loop(data->mlx);
	return (0);
}

void	initialize_main_vars(t_data *data)
{
	data->board = 0;
	data->map_x_tot = 0;
	data->map_y_tot = 0;
	data->px = 64;
}

void	ft_check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (1);
	}
}
