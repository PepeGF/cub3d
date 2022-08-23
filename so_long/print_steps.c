/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:00:47 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/29 18:48:50 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_steps(t_data data)
{
	char	*str;
	char	*end;

	str = ft_itoa(data.mov_cont);
	end = ft_strjoin("Steps: ", str);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.field,
		(0 * data.px), (0 * data.px));
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.border,
		(0 * data.px), (0 * data.px));
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.field,
		(1 * data.px), (0 * data.px));
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.border,
		(1 * data.px), (0 * data.px));
	mlx_string_put(data.mlx, data.mlx_win, 40, 10, 0x000000, end);
	free(str);
	free(end);
}
