/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:05:56 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 18:20:02 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *ft_select_player_orientation(t_data *data)
{
	if (data->board[data->player.y][data->player.x].type == 'N')
		return (ft_strdup("./img/arrow_90.xpm"));
	if (data->board[data->player.y][data->player.x].type == 'S')
		return (ft_strdup("./img/arrow_270.xpm"));
	if (data->board[data->player.y][data->player.x].type == 'E')
		return (ft_strdup("./img/arrow_0.xpm"));
	if (data->board[data->player.y][data->player.x].type == 'W')
		return (ft_strdup("./img/arrow_180.xpm"));
	else
		return (NULL);
}

void	initialize_images(t_data *data, int cont[2])
{
	char *initial_player_orientation;

	initial_player_orientation = ft_select_player_orientation(data);
	data->px = 16;
	data->mlx = mlx_init();
	data->field = mlx_xpm_file_to_image(data->mlx,
			"./img/gris.xpm", &data->px, &data->px);
	data->dino = mlx_xpm_file_to_image(data->mlx,
			initial_player_orientation, &data->px, &data->px);
	free(initial_player_orientation);
	data->food = mlx_xpm_file_to_image(data->mlx,
			"./img/azul.xpm", &data->px, &data->px);
	data->border = mlx_xpm_file_to_image(data->mlx,
			"./img/rojo.xpm", &data->px, &data->px);
	data->obs = mlx_xpm_file_to_image(data->mlx,
			"./img/rosa.xpm", &data->px, &data->px);
/* 	data->end = mlx_xpm_file_to_image(data->mlx,
	 		"./img/amarillo.xpm", &data->px, &data->px); */
	data->mlx_win = mlx_new_window(data->mlx, data->px * cont[0],//bien
			data->px * cont[1], "so_long");//bien
}

void	initialize_main_vars(t_data *data, int cont[2])
{
	data->board = 0;
	data->cont = 0;
	cont[0] = 0;
	cont[1] = 0;
	data->mov_cont = 0;
}

void	free_main_vars(t_data *data, t_list **list, int x)
{
	free(data->mlx);
	free(data->mlx_win);
	free_variables(list);
	free_variables_board(data->board, x);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_list	*list;
	int		cont[2];

	list = 0;
	initialize_main_vars(&data, cont);
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (0);
	}
	list = ft_read_map(argv[1], cont);
	data.board = ft_final_matrix(&list, cont);
	data.cont = sum_cont(data.board, cont);
	// check_map(data.board, cont);
	// check_counters(data.cont);
	data.px = 16;
	data.camera = initialize_camera();//para raycast
	data.player = where_is_the_player(data.board, data.cont->x, data.cont->y, data);
	initialize_images(&data, cont);
	put_field(data.board, cont[1], cont[0], data);
	replace_field(data.board, cont[1], cont[0], data);
	mlx_key_hook(data.mlx_win, &key_hook, &data);
	mlx_hook(data.mlx_win, 17, (1L << 17), &exit_game, &data.mlx);
	mlx_loop(data.mlx);
	free_main_vars(&data, &list, cont[1]);
	return (0);
}
