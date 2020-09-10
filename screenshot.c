/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:35:55 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 18:31:23 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_bmp(t_data *data)
{
	int		fd;
	int		size;
	int		pad;

	system("killall afplay");
	if (ft_strlen(data->save_str) != 6 || (ft_strncmp(data->save_str,
		"--save", 6)) != 0)
		exit_program_data(data, 1);
	pad = (4 - ((int)data->resx * 3) % 4) % 4;
	size = 54 + (3 * ((int)data->resx + pad) * (int)data->resy);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 777)) < 0)
		exit_program_data(data, 7);
	if (!write_bmp_header(fd, size, data))
		exit_program_data(data, 7);
	if (!write_bmp_data(fd, data, pad))
		exit_program_data(data, 7);
	close(fd);
	exit(EXIT_SUCCESS);
}

int		write_bmp_header(int fd, int size, t_data *data)
{
	int				i;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, size);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_in_char(bmpfileheader + 18, data->resx);
	set_int_in_char(bmpfileheader + 22, data->resy);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		write_bmp_data(int file, t_data *data, int pad)
{
	int					y;
	int					x;
	int					color;
	const unsigned char zero[3] = {0, 0, 0};

	y = 0;
	while (y < (int)data->resy)
	{
		x = 0;
		while (x < (int)data->resx)
		{
			color = get_color(data, x, y);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0)
				write(file, &zero, pad);
			x++;
		}
		y++;
	}
	return (1);
}

int		get_color(t_data *data, int x, int y)
{
	if (x >= 0 && x < data->resx
		&& y >= 0 && y < data->resy)
	{
		return (*(int *)(data->image.addr
			+ (4 * data->resx * ((int)data->resy - 1 - y))
			+ (4 * x)));
	}
	return (0x0);
}
