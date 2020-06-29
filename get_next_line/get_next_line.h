/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:52:45 by isfernan          #+#    #+#             */
/*   Updated: 2020/06/26 19:16:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "/mnt/c/Users/isabe/OneDrive/Escritorio/Mío/42Madrid/cub3d/libft/libft.h"
//# include "/Users/isfernan/42cursus/miniRT/miniRT_fake/libft/libft.h"

void	ft_gnl(char *buff[], char **line, int *nb, int fd);
int		ft_read(int fd, char str[], char *buff[]);
int		get_next_line(int fd, char **line);
#endif
