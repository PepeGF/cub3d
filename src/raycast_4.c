# include "../inc/cub3d.h"

void	raycast(t_data *data, t_ray **ray, t_player *player)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray[x]->camera_x = 2 * x / (double)WIN_WIDTH - 1;
		ray[x]->ray_dir_x = player->dir_x + player->plane_x * ray[x]->camera_x;
		ray[x]->ray_dir_y = player->dir_y + player->plane_y * ray[x]->camera_x;
		x++;
	}
	if (data->debug == false)
	x = 0;
	{
		while (x < WIN_WIDTH)
		{

			printf("Rayo: %3d | ", x);
			x++;
		}
	}
}

t_ray	**initialize_ray(void)
{
	t_ray	**ray;
	int		i;

	i = 0;
	ray = malloc(sizeof(t_ray) * WIN_WIDTH);
	while (i < WIN_WIDTH)
	{
		ray[i] = malloc(sizeof(t_ray));
		*ray[i] = (t_ray){};
		i++;
	}
	return (ray); //hay que liberar esto
}