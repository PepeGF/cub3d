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
#  define WIN_WIDTH 1024//512//320
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

enum e_constant_values
{
	vision_angle = 90,
	window_height = 720,
	window_width = 1280
};

typedef struct s_board {
	int		col;
	int		row;
	char	type;
	int		is_border;
	int		jug;
	int		coll;
	// int		end;
}	t_board;

typedef struct s_player
{
	double	x;				//posicion cuadricula
	double	y;
	int		x_fut;			//futura posición x en cuadrícula previa a comprobar colisiones
	int		y_fut;
	int		direction;		//angulo sexagesimal 0 = este, positivo antihorario (anguloRotacion)
	double	dir_rad;		
	int		x_position;		//posicion pixeles
	int		y_position;
	int		x_fut_pos;	//futura posicion x en pixeles previa a comprobar colisiones
	int		y_fut_pos;
	int		move_on;		//0 = parado, 1 = adelante, -1 = atrás
	int		turn_on;		//-1 = giro Izq, 1 = giro Dcha
	int		sideway_on;		//0 = parad0, -1 = derecha, 1 = izquierda
	int		move_speed;		// velocidad desplazamiento en pixeles ¿3?
	int		turn_speed;		// velocidad rotacion. 3 * PI/180 ¿3? grados pasados a radianes
	int		x_view;			// para dibujar hacia dónde mira el jugador, solo para debug, creo
	int		y_view;

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
}	t_ray;

/* 
typedef struct s_ray //casi bueno
{
	int		ray_up;
	int		ray_left;
	int		collision_x_v;
	int		collision_y_v;
	int		collision_x_h;
	int		collision_y_h;
	int		collision_x;
	int		collision_y;
	float	direction_rad;	//rray direction in radians
	float	direction_deg;	//ray direction in degrees
	int		x_step;
	int		y_step;
	bool	h_crash;
	bool	v_crash;
	int		tile_x;
	int		tile_y;
	float	dist_h_collision;
	float	dist_v_collision;
	float	dist;
	char	chosen;
	char	face; //hacia dónde mira la pared (no desde dónde se mira)
	int		wall_height;
	int		color;
	int		column;
	int		draw_start;
	int		draw_end;
}	t_ray;
 */
/* 
typedef struct s_ray
{
	float	ray_x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_direction; // angulo en radianes
	int		ray_up;		// para hacer la colisión correctamente cuando sube
	int		ray_left;	// idem para cuando va hacia la izquierda
	int		collision_x; // x del punto de colision
	int		collision_y; // y del punto de colision
	int		collision_x_h; // x del punto de colision horizontal
	int		collision_y_h; // y del punto de colision horizontal
	int		collision_x_v; // x del punto de colision vertical
	int		collision_y_v; // y del punto de colision vertical
	float	dist_h_collision;
	float	dist_v_collision;
	int		column;	//pixel de la ventana 
	int		h_crash; //booleano de si la colision es horizontal
	int		v_crash; //booleano de si la colision es vertical
	float		x_step;	//distancia en px entre las colisiones parciales en x
	float		y_step;	//distancia en px entre las colisiones parciales en y
	int		tile_x;
	int		tile_y;
	float		*dist;
}	t_ray;
	//float	delta_angle; //angulo desde el rayo central en radianes
 */

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*field;
	void		*obs;
	void		*border;
	int			map_x_tot;
	int			map_y_tot;
	int			px;
	t_board		**board;
	t_player	*player;
	t_ray		**ray;
	bool		debug;
	int			floor_color;
	int			sky_color;
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

// window.c
void		put_field(t_board **matrix, int row, int col, t_data *data);
void		replace_field(t_board **matrix, int row, int col, t_data *data);
void		draw_full_map(t_board **matrix, int row, int col, t_data *data);
void		replace_border_img(t_board **matrix, int row, int col, t_data *data);
void		replace_player_img(t_board **matrix, int row, int col, t_data *data);
void		draw_player(t_data *data);
void		draw_floor2d(t_data	*data);
void 		draw_view_point(t_data *data);

void		draw_raycast_floor(t_data *data);


// key_pressed.c
int			key_hook(int keycode, t_data *data);

// movement.c
void		turn(t_data *data, int keycode);
void		front_back(t_data *data, int keycode);
void		side_move(t_data *data, int keycode);
int			get_future_pos_from_player_pixel(t_data *data, int player_pos_x_temp,
			int	 player_pos_y_temp);
int			check_x_collision(t_data *data, int	player_pos_x_temp);
int			check_y_collision(t_data *data, int	player_pos_y_temp);
void		set_current_grid(t_data *data);

//raycast_4

void		raycast(t_data *data, t_ray **ray, t_player *player);
t_ray		**initialize_ray(void);

/* // raycast.c

t_ray		**initialize_ray(void);
void		raycast(t_data *data);
void		set_ray_basic(t_data *data, t_player *player, t_ray **ray, int i);
void		calculate_first_ray_collision_horizontal(t_data *data, 
				t_board **board, t_ray *ray, t_player *player);
void		calculate_first_ray_collision_vertical(t_data *data,
				t_board **board, t_ray *ray, t_player *player);
void		collision(t_data *data, t_board **board, t_player *player,
				t_ray *ray);
void		calculate_ray_wall_collision_horizontal(t_data *data,
				t_board **board, t_player *player, t_ray *ray);
void		calculate_ray_wall_collision_vertical(t_data *data,
				t_board **board, t_player *player, t_ray *ray);
void		choose_closer_collision(t_data *data, t_player *player, t_ray *ray);
void		calculate_face(t_ray *ray);
void		calculate_wall_height(t_data *data, t_ray *ray);
void		calculate_column(t_data *data, t_ray *ray);
void		calculate_color(t_ray *ray);//solo sin textura, quitar
 */
// visualize
void    visualize_no_texture(t_data *data, t_ray **ray);




// exit_game.c
int	exit_game(t_data *data);

#endif