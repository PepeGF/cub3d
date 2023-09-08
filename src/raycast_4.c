# include "../inc/cub3d.h"

void	raycast(t_data *data, t_ray **ray, t_player *player)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		ray[i]->camera_x = 2 * i / (double)WIN_WIDTH - 1;
		ray[i]->ray_dir_x = player->dir_x + player->plane_x * ray[i]->camera_x;
		ray[i]->ray_dir_y = player->dir_y + player->plane_y * ray[i]->camera_x;
		ray[i]->map_x = (int)player->x;
		ray[i]->map_y = (int)player->y;
		i++;
	}
	if (data->debug == false)
	i = 0;
	{
		while (i < WIN_WIDTH)
		{

			printf("Rayo: %3d | ", i);
			i++;
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