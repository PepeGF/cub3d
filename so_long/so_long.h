/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   so_long.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pmoreno- <pmoreno-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/04/11 20:55:00 by pmoreno-		  #+#	#+#			 */
/*   Updated: 2022/04/27 20:35:28 by pmoreno-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <errno.h>
# include "libft.h"
# include "gnl/get_next_line.h"
# include <mlx.h>

typedef struct s_board {
	int		col;
	int		row;
	char	type;
	int		is_border;
	int		jug;
	int		coll;
	int		end;
}	t_board;

typedef struct s_cont {
	int	jug;
	int	coll;
	int	end;
	int	x;
	int	y;
}	t_cont;

typedef struct s_player {
	int	x;
	int	y;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*field;
	void		*dino;
	void		*food;
	void		*obs;
	void		*border;
	void		*end;
	int			px;
	int			mov_cont;
	t_board		**board;
	t_cont		*cont;
	t_player	player;	
}	t_data;

// check_matrix_cont.c
void		check_player(t_cont *cont);
void		check_end(t_cont *cont);
void		check_collectionables(t_cont *cont);
void		check_counters(t_cont *cont);
t_cont		*sum_cont(t_board **board, int cont[2]);

// check_matrix_values.c
void		check_map_values(t_board **board, int x, int y);
void		check_map_border(t_board **board, int x, int y);

// check_matrix.c
void		check_map(t_board **board, int cont[2]);

// exit_game.c
int			exit_game(t_data *data);

// first_window_images.c
void		put_field(t_board **matrix, int row, int col, t_data data);
void		replace_field(t_board **matrix, int row, int col, t_data data);

// free_variables.c
void		free_variables(t_list **list);
void		free_variables_board(t_board **list, int fil);

// go_down.c
void		go_down(t_data *data);

// go_left.c
void		go_left(t_data *data);

// go_right.c
void		go_right(t_data *data);

// go_up.c
void		go_up(t_data *data);

// key_pressed.c
void		steps(t_data *data);
int			key_hook(int keycode, t_data *data);

// make_movement.c
void		end_game(t_data *data, int x, int y);
void		move_player(t_data *data, int x, int y);
void		check_if_colleccionable(t_data *data);

// matrix.c
void		ft_initialize_pos(t_board *elem);
t_board		ft_add_line_to_lit_list(char c, int fil, int col);
t_board		**ft_final_matrix(t_list **list, int cont[2]);

// player_functions.c
int			is_player(t_board **board, int i, int j);
t_player	where_is_the_player(t_board **board, int x, int y);

// utils.c
void		print_list(t_list **list);
void		print_matrix(t_board **matrix, int x, int y);

// print_steps.c
void		print_steps(t_data data);

// read_file.c
void		free_if_error(int fd, t_list **aux);
void		check_file(char *file);
t_list		*ft_read_map(char *file, int cont[2]);

// replace_imgs.c
void		replace_player_img(t_board **matrix, int row, int col, t_data data);
void		replace_exit_img(t_board **matrix, int row, int col, t_data data);
void		replace_col_img(t_board **matrix, int row, int col, t_data data);
void		replace_border_img(t_board **matrix, int row, int col, t_data data);

// utils.c
void		print_list(t_list **list);
void		print_matrix(t_board **matrix, int x, int y);

#endif
