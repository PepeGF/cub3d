/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:02:48 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/27 11:34:42 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <ctype.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# define BUFFER_SIZE 10

char	*get_next_line(int fd);
char	*ft_final_line(char **rest, int pos);
int		ft_file(char **rest, int pos);
int		ft_read_more(int fd, char **str);
char	*ft_check_buffer(int fd, char *rest);
size_t	ft_strlen_gnl(char *s);
size_t	ft_strlcpy_gnl(char *dst, char *src, size_t dstsize);
char	*ft_strlcat_gnl(char *dst, char *src);
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);

#endif
