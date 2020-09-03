/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:08:36 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/03 19:08:53 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dvector	create_dvec(double i, double j)
{
	t_dvector	vector;

	vector.x = i;
	vector.y = j;
	return (vector);
}

t_ivector	create_ivec(int i, int j)
{
	t_ivector	vector;

	vector.x = i;
	vector.y = j;
	return (vector);
}

void	initialize_keys(t_data *data)
{
	data->key.backwards = 0;
	data->key.towards = 0;
	data->key.right = 0;
	data->key.left = 0;
	data->key.arrow_left = 0;
	data->key.arrow_right = 0;
	data->key.esc = 0;
}

int		find_key_pressed(t_data *data)
{
	int n;

	n = 0;
	if (data->key.towards == 1)
		n++;
	if (data->key.backwards == 1)
		n++;
	if (data->key.right == 1)
		n++;
	if (data->key.left == 1)
		n++;
	if (data->key.arrow_left == 1)
		n++;
	if (data->key.arrow_right == 1)
		n++;
	return (n);
}

int		nb_sign(int a)
{
	if (a < 0)
		return (-1);
	else
		return (0);
}

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

char	check_order(t_data *data)
{
	int		i;
	char	flag;

	i = 0;
	flag = 'V';
	while (i < data->spr.num - 1)
	{
		if (data->spr.arr[i][3] < data->spr.arr[i + 1][3])
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