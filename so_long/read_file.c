/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josgarci <josgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:01:35 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/09/30 16:39:15 by josgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_if_error(int fd, t_list **aux)
{
	free_variables(aux);
	close(fd);
	exit (0);
}

void	check_file(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (file[i] != 'r' || file[i - 1] != 'e'
		|| file[i - 2] != 'b' || file[i - 3] != '.')
	{
		printf("Error\nIncorrect file extension\n");
		exit (0);
	}
}

t_list	*ft_read_map(char *file, int cont[2])
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
	cont[0] = ft_strlen(line) - 1;//esto no valdrá, el mapa no tiene xq ser rectangular
	aux = 0;
	while (line)
	{
		len = ft_strlen(line) - 1;
		if (cont[0] != len)//no vale, las lineas no tienen q ser iguales
			free_if_error(fd, &aux);
		ft_lstadd_back(&aux, ft_lstnew(line));
		line = get_next_line(fd);
		cont[1]++;
	}
	close(fd);
	return (aux);
}
