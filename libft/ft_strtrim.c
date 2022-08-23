/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:00:55 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/25 19:31:43 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_position(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (ft_strchr(s, c))
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_start_position(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && i < ft_strlen(s1))
	{
		if (ft_position(set, s1[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static size_t	ft_end_position(char const *s1, char const *set, size_t pos)
{
	size_t	i;
	size_t	cont;

	i = ft_strlen(s1) - 1;
	cont = 0;
	while (i > 0 && i > pos)
	{
		if (ft_position(set, s1[i]))
		{
			cont++;
			i--;
		}
		else
			break ;
	}
	return (cont);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	pos[2];
	char	*aux;

	if (s1 == 0 || set == 0)
		return (0);
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
	{
		aux = ft_strdup(s1);
		return (aux);
	}
	i = 0;
	pos[0] = ft_start_position(s1, set);
	pos[1] = ft_end_position(s1, set, pos[0]);
	aux = malloc(sizeof(char) * (ft_strlen(s1) - pos[0] - pos[1] + 1));
	if (aux == 0)
		return (0);
	ft_strlcpy(aux, &s1[pos[0]], ft_strlen(s1) - pos[0] - pos[1] + 1);
	return (aux);
}
