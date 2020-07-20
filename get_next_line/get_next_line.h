/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:52:45 by isfernan          #+#    #+#             */
/*   Updated: 2020/07/20 15:55:34 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "/Users/isfernan/42cursus/cub3d/cub3d_fake/libft/libft.h"
//# include "/Users/isfernan/42cursus/miniRT/miniRT_fake/libft/libft.h"

void	ft_gnl(char *buff[], char **line, int *nb, int fd);
int		ft_read(int fd, char str[], char *buff[]);
int		get_next_line(int fd, char **line);
#endif
