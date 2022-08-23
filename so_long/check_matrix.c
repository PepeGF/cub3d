/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:22:42 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/11 18:23:27 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(t_board **board, int cont[2])
{
	check_map_values(board, cont[0], cont[1]);
	check_map_border(board, cont[0], cont[1]);
}
