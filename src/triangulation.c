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
void	ft_swap_points(t_data *data, t_point *point0, t_point *point1)
{
	t_point	aux;

	aux.x = point0->x;
	aux.y = point0->y;
	point0->x = point1->x;
	point0->y = point1->y;
	point1->x = aux.x;
	point1->y = aux.y;
	ft_decide_line(data, *point0, *point1);
	aux.x = point0->x;
	aux.y = point0->y;
	point0->x = point1->x;
	point0->y = point1->y;
	point1->x = aux.x;
	point1->y = aux.y;
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

	dx = point1.x - point0.x;
	dy = point1.y - point0.y;
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

void	prepare_point_to_bresenham(t_data *data, int x_collision, int y_collision)
{
	data->collision = malloc(sizeof (t_point)); //no liberado
	data->player_point = malloc(sizeof (t_point)); //no liberaddo
	data->collision->x = x_collision;
	data->collision->y = y_collision;
	data->player_point->x = data->player_point->x;
	data->player_point->y = data->player_point->y;
}