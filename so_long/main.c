/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:05:56 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/12/06 17:58:38 by josgarci         ###   ########.fr       */
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
	data->mov_cont = 0;//no hace falta
	data->px = 16;
}

void	free_main_vars(t_data *data, t_list **list, int x)
{
	free(data->mlx);
	free(data->mlx_win);
	free_variables(list);
	free_variables_board(data->board, x);
}

void leakss(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_list	*list;
	int		cont[2];
// atexit(leakss);
	list = 0;
	initialize_main_vars(&data, cont);
	if (argc != 2)
	{
		printf("Error en el número de argumentos\n");
		exit (0);
	}
	list = ft_read_map(argv[1], cont);//algunas cosas de esta no valen
	data.board = ft_final_matrix(&list, cont);
	data.cont = sum_cont(data.board, cont);//esta no va a hacer falta, creo
	// check_map(data.board, cont);
	// check_counters(data.cont);
	// data.px = 16; //metido en función de initializa_main_vars
	data.ray = initialize_ray();//para raycast, hecha en las primeras pruebas, sin utilidad clara aún
	data.player = where_is_the_player(data.board, cont[0], cont[1]);//inicializa los datos geometricos del jugador. MUY IMPORTANTE
	initialize_images(&data, cont);
	// printf("X ini: %d, Y ini: %d\n",data.player.x, data.player.y);
	ft_set_player_intial_geometry(data, &(data.player));
	put_field(data.board, cont[1], cont[0], data);
	// print_matrix(data.board, cont[0], cont[1]);
	replace_field(data.board, cont[1], cont[0], data);
	// mlx_key_hook(data.mlx_win, &key_hook, &data);
	mlx_hook(data.mlx_win, 2, 0/* (1L << 17) */, &key_hook, &data.mlx);//captar pulsaciones mantenidas, investigar cómo evitar micropausa entre primera pulsacion y las demás
	mlx_hook(data.mlx_win, 17, 0/* (1L << 17) */, &exit_game, &data.mlx);
	mlx_loop(data.mlx);
	free_main_vars(&data, &list, cont[1]);
	return (0);
}

// continuar con raycasting, min 0:00 de este video:
// https://www.youtube.com/watch?v=awXyP0g91mE