/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:51:58 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/27 17:44:48 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_floor2d(t_data	data)
{
	int	i;
	int j;
//un cuadradito de 5x5 pix del color de fondo
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_pixel_put(data.mlx, data.mlx_win, data.player.x_position + i, data.player.y_position + j, 0xC3C3C3);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data data)
{
	int	i;
	int j;
//un cuadradito de 5x5 pix
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_pixel_put(data.mlx, data.mlx_win, data.player.x_position + i, data.player.y_position + j, 0x000000);
			j++;
		}
		i++;
	}
}

void	replace_player_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;
(void)data;
	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
		{
			if (matrix[i][j].type == 'N' || matrix[i][j].type == 'S'
				|| matrix[i][j].type == 'E' || matrix[i][j].type == 'W')
				draw_player(data);
				// mlx_put_image_to_window(data.mlx, data.mlx_win, data.dino,
				// 	(matrix[i][j].col * data.px),
				// 	(matrix[i][j].row * data.px));
			j++;
		}
	}
}

/* void	replace_exit_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < col)
	{
		j = 0;
		while (j < row)
		{
			if (matrix[i][j].type == 'E')
				mlx_put_image_to_window(data.mlx, data.mlx_win, data.dino,//cambiado data.end por dta.dino
					(matrix[i][j].col * data.px),
					(matrix[i][j].row * data.px));
			j++;
		}
	}
} */

/* void	replace_col_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < col)
	{
		j = 0;
		while (j < row)
		{
			if (matrix[i][j].type == 'C')
				mlx_put_image_to_window(data.mlx, data.mlx_win, data.food,
					(matrix[i][j].col * data.px),
					(matrix[i][j].row * data.px));
			j++;
		}
	}
} */

void	replace_border_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
		{
			if (matrix[i][j].type == '1')
			{
				if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
					mlx_put_image_to_window(data.mlx, data.mlx_win, data.border,
						(matrix[i][j].col * data.px),
						(matrix[i][j].row * data.px));
				else
					mlx_put_image_to_window(data.mlx, data.mlx_win, data.obs,
						(matrix[i][j].col * data.px),
						(matrix[i][j].row * data.px));
			}
			j++;
		}
	}
}
