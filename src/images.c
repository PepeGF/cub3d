/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:08:29 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/24 18:12:21 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	initialize_images(t_data *data)
{
	data->px = 64;
	data->mlx = mlx_init();
	data->cub3d_image = malloc(sizeof(t_img));
	*(data->cub3d_image) = (t_img){};
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	data->cub3d_image->img_data = mlx_new_image(data->mlx, WIN_WIDTH,
			WIN_HEIGHT);
	data->cub3d_image->addr = mlx_get_data_addr(data->cub3d_image->img_data,
			&data->cub3d_image->bits_per_pixel, &data->cub3d_image->line_length,
			&data->cub3d_image->endian);
	data->sky_color = 0xABCDEF;
	data->floor_color = 0x123456;
	init_texture(data);
}

void	init_texture(t_data *data)
{
	texture_malloc(data);
	data->no->img_data = mlx_xpm_file_to_image(data->mlx, data->no->path,
			&(data->no->width), &(data->no->height));
	data->so->img_data = mlx_xpm_file_to_image(data->mlx, data->so->path,
			&(data->so->width), &(data->so->height));
	data->ea->img_data = mlx_xpm_file_to_image(data->mlx, data->ea->path,
			&(data->ea->width), &(data->ea->height));
	data->we->img_data = mlx_xpm_file_to_image(data->mlx, data->we->path,
			&(data->we->width), &(data->we->height));
	data->no->addr = mlx_get_data_addr(data->no->img_data,
			&(data->no->bits_per_pixel), &(data->no->line_length),
			&(data->no->endian));
	data->so->addr = mlx_get_data_addr(data->so->img_data,
			&(data->so->bits_per_pixel),
			&(data->so->line_length), &(data->so->endian));
	data->ea->addr = mlx_get_data_addr(data->ea->img_data,
			&(data->ea->bits_per_pixel), &(data->ea->line_length),
			&(data->ea->endian));
	data->we->addr = mlx_get_data_addr(data->we->img_data,
			&(data->we->bits_per_pixel),
			&(data->we->line_length), &(data->we->endian));
}

void	texture_malloc(t_data *data)
{
	data->no = (t_img *)malloc(sizeof(t_img));
	data->so = (t_img *)malloc(sizeof(t_img));
	data->ea = (t_img *)malloc(sizeof(t_img));
	data->we = (t_img *)malloc(sizeof(t_img));
	// data->no->path = ft_strdup("./img/NO.xpm");
	data->no->path = ft_strdup("./img/Tiamant.xpm");
	// data->so->path = ft_strdup("./img/SO.xpm");
	data->so->path = ft_strdup("./img/Marventis.xpm");
	// data->ea->path = ft_strdup("./img/EA.xpm");
	data->ea->path = ft_strdup("./img/Ignisaria.xpm");
	// data->we->path = ft_strdup("./img/WE.xpm");
	data->we->path = ft_strdup("./img/Zefiria.xpm");
}
