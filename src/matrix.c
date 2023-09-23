/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:40:50 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 20:19:32 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_board	**ft_final_matrix(t_list **list, t_data *data)
{
	t_board	**board;
	t_list	*aux;
	int		i;
	int		j;

	i = 0;
	aux = *list;
	board = malloc(sizeof(t_board *) * (data->map_y_tot));
	while (i < data->map_y_tot)
	{
		j = 0;
		board[i] = malloc(sizeof(t_board) * (data->map_x_tot));
		while (j < data->map_x_tot)
		{
			board[i][j] = ft_add_line_to_list(aux->content[j], i, j);
			j++;
		}
		i++;
		aux = aux->next;
	}
	return (board);
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
	return (elem);
}

void	ft_initialize_pos(t_board *elem)
{
	elem->col = -1;
	elem->row = -1;
	elem->is_border = 0;
	elem->coll = 0;
	elem->jug = 0;
}
