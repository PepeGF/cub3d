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

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1042
# endif

typedef struct s_board {
	int		col;
	int		row;
	char	type;
	int		is_border;
	int		jug;
	int		coll;
	// int		end;
}	t_board;

typedef struct s_cont {
	int	jug;
	int	coll;
	int	end;
	int	x;
	int	y;
}	t_cont;

typedef struct s_player 
{
	int	x;				//posicion cuadricula
	int	y;
	int	x_fut;			//futura posición x en cuadrícula previa a comprobar colisiones
	int	y_fut;
	int	direction;		//angulo sexagesimal 0 = este, positivo antihorario (anguloRotacion)
	double	x_position;		//posicion pixeles
	double	y_position;
	double	x_fut_pos;	//futura posicion x en pixeles previa a comprobar colisiones
	double	y_fut_pos;
	int	x_dir_vect;		//vector dirección
	int	y_dir_vect;
	int	move_on;		//0 = parado, 1 = adelante, -1 = atrás
	int	turn_on;		//-1 = giro Izq, 1 = giro Dcha
	int	sideway_on;		//0 = parad0, -1 = derecha, 1 = izquierda
	int	move_speed;		// velocidad desplazamiento en pixeles ¿3?
	int	turn_speed;		// velocidad rotacion. 3 * PI/180 ¿3? grados pasados a radianes

}	t_player;

typedef struct s_ray
{
	double	ray_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_direction; // angulo en radianes
	double	delta_angle; //angulo desde el rayo central en radianes
	int		ray_up;		// para hacer la colisión correctamente cuando sube
	int		ray_left;	// idem para cuando va hacia la izquierda
	int		collision_x; // x del punto de colision
	int		collision_y; // y del punto de colision
	int		collision_x_h; // x del punto de colision horizontal
	int		collision_y_h; // y del punto de colision horizontal
	int		collision_x_v; // x del punto de colision vertical
	int		collision_y_v; // y del punto de colision vertical
	int		next_x_h;
	int		next_y_h;
	int		next_x_v;
	int		next_y_v;
	int		column;	//pixel de la ventana 
	int		h_crash; //booleano de si la colision es horizontal
	int		v_crash; //booleano de si la colision es vertical
	int		x_step;	//distancia en px entre las colisiones parciales en x
	int		y_step;	//distancia en px entre las colisiones parciales en y
	int		tile_x;
	int		tile_y;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*field;
	void		*dino;
	void		*food;
	void		*obs;
	void		*border;
	// void		*end;
	int			map_x_tot;
	int			map_y_tot;
	int			px;
	int			mov_cont;
	t_board		**board;
	t_cont		*cont;
	t_player	player;
	t_ray		*ray;
}	t_data;

// main.c
void	initialize_main_vars(t_data *data);
void	ft_check_argc(int argc);

// read_file.c
t_list	*ft_read_map(char *file, t_data *data);
void	check_file(char *file);

// matrix.c
t_board	**ft_final_matrix(t_list **list, t_data *data);
t_board	ft_add_line_to_list(char c, int row, int col);
void	ft_initialize_pos(t_board *elem);





#endif