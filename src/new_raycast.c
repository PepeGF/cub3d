#include "../inc/cub3d.h"

t_ray	*initialize_ray(void)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	*ray = (t_ray){};
	return (ray); //hay que liberar esto
}

// https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/