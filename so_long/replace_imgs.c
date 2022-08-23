/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:51:58 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/27 20:52:21 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	replace_player_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < col)
	{
		j = 0;
		while (j < row)
		{
			if (matrix[i][j].type == 'P')
				mlx_put_image_to_window(data.mlx, data.mlx_win, data.dino,
					(matrix[i][j].col * data.px),
					(matrix[i][j].row * data.px));
			j++;
		}
	}
}

void	replace_exit_img(t_board **matrix, int row, int col, t_data data)
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
				mlx_put_image_to_window(data.mlx, data.mlx_win, data.end,
					(matrix[i][j].col * data.px),
					(matrix[i][j].row * data.px));
			j++;
		}
	}
}

void	replace_col_img(t_board **matrix, int row, int col, t_data data)
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
}

void	replace_border_img(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < col)
	{
		j = 0;
		while (j < row)
		{
			if (matrix[i][j].type == '1')
			{
				if (i == 0 || j == 0 || i == col - 1 || j == row - 1)
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
