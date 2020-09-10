/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:48:22 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 19:47:46 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop_manager(void *param)
{
	t_data *data;

	data = (t_data *)param;
	key_manager(data);
	return (0);
}

void	key_manager(t_data *data)
{
	if (data->key.esc == 1)
	{
		system("killall afplay");
		exit(EXIT_SUCCESS);
	}
	if (data->key.towards == 1)
		move_towards(data);
	if (data->key.backwards == 1)
		move_backwards(data);
	if (data->key.right == 1)
		move_right(data);
	if (data->key.left == 1)
		move_left(data);
	if (data->key.arrow_right == 1)
		rotate_right(data);
	if (data->key.arrow_left == 1)
		rotate_left(data);
	if (find_key_pressed(data))
		draw_screen(data, data->player);
}

void	rotate_left(t_data *data)
{
	double		dirx;
	double		diry;
	double		planex;
	double		planey;

	dirx = data->player->dir.x;
	diry = data->player->dir.y;
	planex = data->player->cam_plane.x;
	planey = data->player->cam_plane.y;
	data->player->dir.x = cos(-R_SPEED) * dirx - sin(-R_SPEED) * diry;
	data->player->dir.y = sin(-R_SPEED) * dirx + cos(-R_SPEED) * diry;
	data->player->cam_plane.x = cos(-R_SPEED) * planex - sin(-R_SPEED) * planey;
	data->player->cam_plane.y = sin(-R_SPEED) * planex + cos(-R_SPEED) * planey;
}

void	rotate_right(t_data *data)
{
	double		dirx;
	double		diry;
	double		planex;
	double		planey;

	dirx = data->player->dir.x;
	diry = data->player->dir.y;
	planex = data->player->cam_plane.x;
	planey = data->player->cam_plane.y;
	data->player->dir.x = cos(R_SPEED) * dirx - sin(R_SPEED) * diry;
	data->player->dir.y = sin(R_SPEED) * dirx + cos(R_SPEED) * diry;
	data->player->cam_plane.x = cos(R_SPEED) * planex - sin(R_SPEED) * planey;
	data->player->cam_plane.y = sin(R_SPEED) * planex + cos(R_SPEED) * planey;
}

int		close_window(void *data)
{
	(void)data;
    system("killall afplay");
	exit(EXIT_SUCCESS);
	return (0);
}
