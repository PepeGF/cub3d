/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:54:02 by josgarci          #+#    #+#             */
/*   Updated: 2022/04/14 11:32:37 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
 * In case of slope < -1 and dx < 0 start and ending point must be swapped
 * and after draw the line have to return to their original status.
 */
static void	ft_swap_points(t_data *data, t_point *point0, t_point *point1)
{
	t_point	aux;

	aux.x = point0->x_mod;
	aux.y = point0->y_mod;
	point0->x_mod = point1->x_mod;
	point0->y_mod = point1->y_mod;
	point1->x_mod = aux.x;
	point1->y_mod = aux.y;
	ft_decide_line(data, *point0, *point1);
	aux.x = point0->x_mod;
	aux.y = point0->y_mod;
	point0->x_mod = point1->x_mod;
	point0->y_mod = point1->y_mod;
	point1->x_mod = aux.x_mod;
	point1->y_mod = aux.y_mod;
}

/*
 * This function chooses which kind of line must be drawn knowing the 2D coord
 * of the start and ending point.
 */
void	ft_decide_line(t_data *data, t_point point0, t_point point1)
{
	int	dx;
	int	dy;
	int	dd;

	dx = point1.x_mod - point0.x_mod;
	dy = point1.y_mod - point0.y_mod;
	dd = abs(dx) - abs(dy);
	if (dx < 0)
		ft_swap_points(data, &point0, &point1);
	else if (dy < 0 && dd < 0)
		ft_bresen_neg_high(data, point0, point1);
	else if (dy < 0 && dd >= 0)
		ft_bresen_neg_low(data, point0, point1);
	else if (dy >= 0 && dd >= 0)
		ft_bresen_pos_low(data, point0, point1);
	else if (dy > 0 && dd < 0)
		ft_bresen_pos_high(data, point0, point1);
}

