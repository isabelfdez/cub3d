/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:16:08 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/09 18:46:28 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getpath(char *aux, int i, int icpy)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * (icpy - i + 1));
	while (i < icpy)
	{
		str[j] = aux[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*to_base(unsigned int nb)
{
	char	*str;
	char	*base;
	int		j;

	base = "0123456789ABCDEF";
	j = 0;
	str = malloc(sizeof(char) * 3);
	str[1] = base[nb % 16];
	nb = nb / 16;
	if (nb < 10)
		str[0] = nb + '0';
	else
		str[0] = nb - 10 + 'A';
	str[2] = '\0';
	return (str);
}

void	count_sprites(t_data *data)
{
	int		i;
	int		j;

	data->spr.num = 0;
	i = 0;
	while (i < data->l)
	{
		j = 0;
		while (j < data->c)
		{
			if (data->map[i][j] == '2')
				data->spr.num++;
			j++;
		}
		i++;
	}
}

int		check_colors(t_data *data)
{
	if (data->floor.r < 0 || data->floor.r > 255)
		return (0);
	if (data->floor.g < 0 || data->floor.g > 255)
		return (0);
	if (data->floor.b < 0 || data->floor.b > 255)
		return (0);
	if (data->ceil.r < 0 || data->ceil.r > 255)
		return (0);
	if (data->ceil.g < 0 || data->ceil.g > 255)
		return (0);
	if (data->ceil.b < 0 || data->ceil.b > 255)
		return (0);
	return (1);
}

void	exit_program_data(t_data *data, int i)
{	
	int		x;

	x = -1;
	if (i == 1)
		ft_putstr_fd("Error\nInvalid arguments", 2);
	if (i == 2)
		ft_putstr_fd("Error\nInvalid floor/ceiling colors", 2);
	if (i == 3)
		ft_putstr_fd("Error\nInvalid texture", 2);
	if (i == 4)
		ft_putstr_fd("Error\nInvalid sprite texture", 2);
	if (i == 7)
		ft_putstr_fd("Error\nInvalid .bmp file", 2);

	/*free(data->spr.buff);
	while (++x < data->l)
	{
		free(*(data->map + x));
		free(*(data->map2 + x));
	}
	free(data->map);
	free(data->map2);
	free(data->player);*/
	free(data);
	exit(EXIT_FAILURE);
}
