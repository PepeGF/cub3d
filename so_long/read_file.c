/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:01:35 by pmoreno-          #+#    #+#             */
/*   Updated: 2023/07/13 20:47:36 by pmoreno-         ###   ########.fr       */
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
	if (file[i] != 'b' || file[i - 1] != 'u'
		|| file[i - 2] != 'c' || file[i - 3] != '.')
	{
		printf("Error\nIncorrect file extension\n");
		exit (0);
	}
}


int	is_matrix_line(char *line)
{
	int i;

	i = 0;
	while (line[i]!= '\0' && line[i] != '\n')
	{
		//printf("%c --- > ", line[i]);
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] == 'E' && line[i] == ' ')
		{
			//printf("No es letra de matriz");
			return 0;
		}
		if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == 'O') || (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line[i + 1] == 'E'))
		{
			//printf("No es linea de matriz");
			return 0;
		}
		i++;
	}
	return 1;
}


t_list	*ft_read_map(char *file, int cont[2])
{
	int		fd;
	char	*line;
	t_list	*aux;

	check_file(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (line == 0)
		exit(0);
	cont[0] = 0;
	aux = 0;
	while (line)
	{
		//len = ft_strlen(line) - 1;
		// if (cont[0] != len)//no vale, las lineas no tienen q ser iguales
		// 	free_if_error(fd, &aux);
		if (ft_strchr(line, '1') != 0 && is_matrix_line(line))
			cont[1]++;
		if ((int)(ft_strlen(line) - 1) > cont[0])
			cont[0] = ft_strlen(line) - 1;
		ft_lstadd_back(&aux, ft_lstnew(line));
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
	return (aux);
}
