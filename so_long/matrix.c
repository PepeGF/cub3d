/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:51:28 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 14:03:27 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_initialize_pos(t_board *elem)
{
	elem->col = -1;
	elem->row = -1;
	elem->is_border = 0;
	elem->type = 'N';//esto no se puede hacer aquí, se puede, pero no sirve de nada
	elem->coll = 0;
//	elem->end = 0;
	elem->jug = 0;
}

t_board	ft_add_line_to_list(char c, int row, int col)
{
	t_board	elem;

	ft_initialize_pos(&elem);
	elem.col = col;
	elem.row = row;
	elem.type = c;
	if (c == '1')
		elem.is_border = 1;
	// else if (c == 'C')
		elem.coll = 1;
	/* else if (c == 'E')
		elem.end = 1; */
	//else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	//	elem.jug = 1;
	//elem.end = 1;//para que el checker no llore aunque sea mentira
	return (elem);
}

t_board	**ft_final_matrix(t_list **list, int cont[2])
{
	t_board	**board;
	t_list	*aux;
	int		i;
	int		j;

	i = 0;
	aux = *list;
	board = malloc(sizeof(t_board *) * (cont[1])); //bien
	while (i < cont[1])
	{
		j = 0;
		board[i] = malloc(sizeof(t_board) * (cont[0])); //bien
		while (j < cont[0])
		{
			board[i][j] = ft_add_line_to_list(aux->content[j], i, j);
			j++;
		}
		i++;
		aux = aux->next;
	}
	return (board);
}
