/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:08:36 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/04 19:06:15 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

void		initialize_keys(t_data *data)
{
	data->key.backwards = 0;
	data->key.towards = 0;
	data->key.right = 0;
	data->key.left = 0;
	data->key.arrow_left = 0;
	data->key.arrow_right = 0;
	data->key.esc = 0;
	data->info = 0;
}

int			find_key_pressed(t_data *data)
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

int			nb_sign(int a)
{
	if (a < 0)
		return (-1);
	else
		return (0);
}
