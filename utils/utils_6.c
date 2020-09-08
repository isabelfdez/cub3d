/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:16:54 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/08 17:26:00 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	check_order(t_data *data, double **arr)
{
	int		i;
	char	flag;

	i = 0;
	flag = 'V';
	while (i < data->spr.num - 1)
	{
		if (arr[i][3] < arr[i + 1][3])
			flag = 'F';
		i++;
	}
	return (flag);
}

int		number_base(char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = -1;
	while (++i < 6)
	{
		if (ft_isdigit(str[i]))
			nb = nb + pow(16, 5 - i) * (str[i] - '0');
		else
			nb = nb + pow(16, 5 - i) * (str[i] - 'A' + 10);
	}
	return (nb);
}

double	invdet(t_player *player)
{
	double nb;

	nb = 1.0 / (player->cam_plane.x * player->dir.y -
		player->cam_plane.y * player->dir.x);
	return (nb);
}
