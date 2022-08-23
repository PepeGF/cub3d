/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:05:56 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/05/11 19:21:12 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_images(t_data *data, int cont[2])
{
	data->px = 80;
	data->mlx = mlx_init();
	data->field = mlx_xpm_file_to_image(data->mlx,
			"./img/field.xpm", &data->px, &data->px);
	data->dino = mlx_xpm_file_to_image(data->mlx,
			"./img/1.xpm", &data->px, &data->px);
	data->food = mlx_xpm_file_to_image(data->mlx,
			"./img/polloesc2.xpm", &data->px, &data->px);
	data->border = mlx_xpm_file_to_image(data->mlx,
			"./img/border.xpm", &data->px, &data->px);
	data->obs = mlx_xpm_file_to_image(data->mlx,
			"./img/obs2.xpm", &data->px, &data->px);
	data->end = mlx_xpm_file_to_image(data->mlx,
			"./img/cave.xpm", &data->px, &data->px);
	data->mlx_win = mlx_new_window(data->mlx, data->px * cont[1],
			data->px * cont[0], "so_long");
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
	check_map(data.board, cont);
	check_counters(data.cont);
	data.player = where_is_the_player(data.board, data.cont->y, data.cont->x);
	initialize_images(&data, cont);
	put_field(data.board, cont[1], cont[0], data);
	replace_field(data.board, cont[1], cont[0], data);
	mlx_key_hook(data.mlx_win, &key_hook, &data);
	mlx_hook(data.mlx_win, 17, (1L << 17), &exit_game, &data.mlx);
	mlx_loop(data.mlx);
	free_main_vars(&data, &list, cont[0]);
	return (0);
}
