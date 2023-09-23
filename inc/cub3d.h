/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:55:16 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 20:56:40 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <errno.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>

# ifndef WIN_2D_WIDTH
#  define WIN_2D_WIDTH 1536//360//1920
# endif

# ifndef WIN_2D_HEIGHT
#  define WIN_2D_HEIGHT 896//271//1042
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1024//320
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 820//200
# endif

# ifndef FOV
#  define FOV 66
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 20
# endif

# ifndef TURN_SPEED
#  define TURN_SPEED 10
# endif

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 64
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 64
# endif

enum e_keycodes
{
	key_a = 0,
	key_s = 1,
	key_d = 2,
	key_q = 12,
	key_w = 13,
	key_space = 49,
	key_esc = 53,
	key_up = 126,
	key_down = 125,
	key_left = 123,
	key_right = 124
};

enum e_cardinal_points
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 0,
	WEST = 180
};

typedef struct s_board {
	int		col;
	int		row;
	char	type;
	int		is_border;
	int		jug;
	int		coll;
}	t_board;

typedef struct s_player
{
	double	x;
	double	y;
	int		x_fut;
	int		y_fut;
	int		direction;
	double	dir_rad;
	int		x_position;
	int		y_position;
	int		x_fut_pos;
	int		y_fut_pos;
	int		move_on;
	int		turn_on;
	int		sideway_on;
	int		move_speed;
	int		turn_speed;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	bool	hit;
	char	face;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_big_y_start;
	double	tex_big_y_end;
}	t_ray;

typedef struct s_img
{
	void	*img_data;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		index;
	char	*path;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			map_x_tot;
	int			map_y_tot;
	int			px;
	t_board		**board;
	t_player	*player;
	t_ray		**ray;
	bool		debug;
	int			floor_color;
	int			sky_color;
	t_img		*cub3d_image;
	t_img		*no;
	t_img		*so;
	t_img		*ea;
	t_img		*we;
}	t_data;

// main.c
void		initialize_main_vars(t_data *data);
void		ft_check_argc(int argc);

// read_file.c
t_list		*ft_read_map(char *file, t_data *data);
void		check_file(char *file);

// matrix.c
t_board		**ft_final_matrix(t_list **list, t_data *data);
t_board		ft_add_line_to_list(char c, int row, int col);
void		ft_initialize_pos(t_board *elem);

// player_function.c
t_player	*where_is_the_player(t_board **board, int x, int y);
int			is_player(t_board **board, int i, int j);
void		set_player_initial_geometry(t_data *data, t_player *player);
int			ft_player_initial_direction(t_board **board, t_player *player);

// images.c
void		initialize_images(t_data *data);
void		init_texture(t_data *data);
void		texture_malloc(t_data *data);

// key_pressed.c
int			key_hook(int keycode, t_data *data);

// movement.c
void		turn(t_data *data, int keycode);
void		front_back(t_data *data, int keycode);
void		side_move(t_data *data, int keycode);
int			get_future_pos_from_player_pixel(t_data *data,
				int player_pos_x_temp, int player_pos_y_temp);
int			check_x_collision(t_data *data, int player_pos_x_temp);
int			check_y_collision(t_data *data, int player_pos_y_temp);
void		set_current_grid(t_data *data);

//raycast
void		raycast(t_data *data, t_ray **ray, t_player *player);
t_ray		**initialize_ray(void);

// visualize
void		visualize_no_texture(t_data *data, t_ray **ray);

// exit_game.c
int			exit_game(t_data *data);

#endif