# include "../inc/cub3d.h"

t_ray	*initialize_ray(void)//temporal para tener todo inicializado
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	*ray = (t_ray){};
	/* 
		sirve para inicializar en 0 todas las variables de la estructura

	ray->ray_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->ray_direction = 0;
	ray->delta_angle = 0;
	ray->ray_up = 0;
	ray->ray_left = 0;
	ray->collision_x = 0;
	ray->collision_y = 0;
	ray->collision_x_h = 0;
	ray->collision_y_h = 0;
	ray->collision_x_v = 0;
	ray->collision_y_v = 0;
	ray->column = 0;
	ray->h_crash = false;
	ray->v_crash = false; 
	
	no borro todo esto por si me he pasado de listo
	*/

	return (ray); //hay que liberar esto
}

