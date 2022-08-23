/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_window_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:27:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/29 18:49:42 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_field(t_board **matrix, int row, int col, t_data data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < col)
	{
		j = 0;
		while (j < row)
		{
			mlx_put_image_to_window(data.mlx, data.mlx_win, data.field,
				(matrix[i][j].col * data.px), (matrix[i][j].row * data.px));
			j++;
		}
	}
}

void	replace_field(t_board **matrix, int row, int col, t_data data)
{
	replace_border_img(matrix, row, col, data);
	replace_player_img(matrix, row, col, data);
	replace_col_img(matrix, row, col, data);
	replace_exit_img(matrix, row, col, data);
	print_steps(data);
}
