/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:45:14 by josgarci          #+#    #+#             */
/*   Updated: 2023/09/23 20:45:15 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_list	*ft_read_map(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		len;
	t_list	*aux;

	check_file(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == 0)
		exit(0);
	data->map_x_tot = ft_strlen(line) - 1;
	aux = 0;
	while (line)
	{
		len = ft_strlen(line) - 1;
		ft_lstadd_back(&aux, ft_lstnew(line));
		line = get_next_line(fd);
		data->map_y_tot += 1;
	}
	close(fd);
	return (aux);
}

void	check_file(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b' || file[i - 1] != 'u'
		|| file[i - 2] != 'c' || file[i - 3] != '.')
	{
		printf("Error\nIncorrect file extension\n");
		exit (0);
	}
}
