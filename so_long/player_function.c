/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:19:40 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/08/27 14:26:43 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_player_direction(t_board **board, t_player player)
{
	if (board[player.y][player.x].type == 'N')
		return (90);
	if (board[player.y][player.x].type == 'S')
		return (270);
	if (board[player.y][player.x].type == 'W')
		return (180);
	else
		return (0);	
}

int	is_player(t_board **board, int i, int j)
{
	if (board[i][j].type == 'N' || board[i][j].type == 'S'
		|| board[i][j].type == 'E' || board[i][j].type == 'W')
		return (1);
	return (0);
}

int	ft_get_player_x_position(t_player player, t_data data)
{
	int	aux;

	// aux = malloc(sizeof(int) * 2);
	aux = player.x * data.px + data.px / 2;
	printf ("Posición del jugador:\n\tx: %d\n", aux);
	return (aux);//no se cuándo hay que liberar esto...
}

int	ft_get_player_y_position(t_player player, t_data data)
{
	int	aux;

	aux = player.y * data.px + data.px / 2;
	printf ("\ty: %d\n", aux);
	return (aux);//no se cuándo hay que liberar esto...
}
t_player	where_is_the_player(t_board **board, int x, int y, t_data data)
{
	int			i;
	int			j;
	t_player	player;

	i = -1;
	while (++i < y)
	{
		j = 0;
		while (j < x)
		{
			if (is_player(board, i, j))
			{
				player.x = j;
				player.y = i;
				printf("player.x: %d\tplayer.y: %d\tpx: %d", player.x, player.y, data.px);
				player.direction = ft_player_direction(board, player);
				player.x_position = ft_get_player_x_position(player, data);
				player.y_position = ft_get_player_y_position(player, data);
				// player.dir_vector = ft_get_player_direction(board, player);
				break ;
			}	
			j++;
		}
	}
	return (player);
}
