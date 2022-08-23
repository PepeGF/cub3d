/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_board.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:59:43 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/11 18:12:27 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_player(t_cont *cont)
{
	if (cont->jug > 1)
	{
		printf("Error\nToo many players\n");
		exit(0);
	}
	if (cont->jug > 1)
	{
		printf("Error\nThere are not enought players\n");
		exit(0);
	}
}

void	check_end(t_cont *cont)
{
	if (cont->end < 1)
	{
		printf("Error\nWhere is the exit?\n");
		exit(0);
	}
	if (cont->end > 1)
	{
		printf("Error\nThere are a lot of exits!\n");
		exit(0);
	}
}

void	check_collectionables(t_cont *cont)
{
	if (cont->coll < 1)
	{
		printf("Error\nYou have too add some collectionables\n");
		exit(0);
	}
}

void	check_counters(t_cont *cont)
{
	check_player(cont);
	check_end(cont);
	check_collectionables(cont);
}

t_cont	*sum_cont(t_board **board, int cont[2])
{
	int		i;
	int		j;
	t_cont	*aux;

	i = -1;
	aux = malloc(sizeof(t_cont));
	aux->jug = 0;
	aux->coll = 0;
	aux->end = 0;
	aux->x = cont[1];
	aux->y = cont[0];
	while (++i < cont[0])
	{
		j = -1;
		while (++j < cont[1])
		{
			if (board[i][j].type == 'C')
				aux->coll++;
			else if (board[i][j].type == 'E')
				aux->end++;
			else if (board[i][j].type == 'P')
				aux->jug++;
		}
	}
	return (aux);
}
