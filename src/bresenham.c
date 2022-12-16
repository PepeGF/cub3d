/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:47:27 by josgarci          #+#    #+#             */
/*   Updated: 2022/04/14 10:39:32 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
 * Dibuja líneas con pendiente entre 0 y 1.
 */
void	ft_bresen_pos_low(t_data *data, t_point point0, t_point point1)
{
	int	d[3];
	int	coord[2];

	d[0] = point1.x - point0.x;
	d[1] = point1.y - point0.y;
	coord[0] = point0.x;
	coord[1] = point0.y;
	d[2] = 2 * d[1] - d[0];
	while (coord[0] < point1.x)
	{
		if (d[2] >= 0)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			coord[1]++;
			d[2] = d[2] + 2 * d[1] - 2 * d[0];
		}
		else
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			d[2] = d[2] + 2 * d[1];
		}
		coord[0]++;
	}
}

/*
 * Dibuja líneas con pendiente mayor que 1..
 */
void	ft_bresen_pos_high(t_data *data, t_point point0, t_point point1)
{
	int	d[3];
	int	coord[2];

	d[0] = point1.x - point0.x;
	d[1] = point1.y - point0.y;
	coord[0] = point0.x;
	coord[1] = point0.y;
	d[2] = 2 * d[0] - d[1];
	while (coord[1] < point1.y)
	{
		if (d[2] >= 0)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			coord[0]++;
			d[2] = d[2] + 2 * d[0] - 2 * d[1];
		}
		else
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			d[2] = d[2] + 2 * d[0];
		}
		coord[1]++;
	}
}

/*
 * Dibuja líneas con pendiente entre 0 y -1.
 */
void	ft_bresen_neg_low(t_data *data, t_point point0, t_point point1)
{
	int	d[3];
	int	coord[2];

	d[0] = point1.x - point0.x;
	d[1] = point1.y - point0.y;
	coord[0] = point0.x;
	coord[1] = point0.y;
	d[2] = 2 * d[1] - d[0];
	while (coord[0] < point1.x)
	{
		if (d[2] >= 0)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			coord[1]--;
			d[2] = d[2] - 2 * d[1] - 2 * d[0];
		}
		else
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			d[2] = d[2] - 2 * d[1];
		}
		coord[0]++;
	}
}

/*
 * Dibuja líneas con pendiente menor que -1.
 */
void	ft_bresen_neg_high(t_data *data, t_point point0, t_point point1)
{
	int	d[3];
	int	coord[2];

	d[0] = point1.x - point0.x;
	d[1] = point1.y - point0.y;
	coord[0] = point1.x;
	coord[1] = point1.y;
	d[2] = 2 * d[1] - d[0];
	while (coord[1] < point0.y)
	{
		if (d[2] >= 0)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			coord[0]--;
			d[2] = d[2] + 2 * d[0] + 2 * d[1];
		}
		else
		{
			mlx_pixel_put(data->mlx, data->mlx_win, coord[0], coord[1], 0xFF0000);
			d[2] = d[2] + 2 * d[0];
		}
		coord[1]++;
	}
}
