/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 16:36:30 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:45:51 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_raycasting(t_data *data)
{
	t_player	*player;
	int			x;

	x = 0;
	openwindow(data);
	if (!(player = malloc(sizeof(t_player))))
		return ;
	player->pos.x = col_character(data) + 0.5;
	player->pos.y = line_character(data) + 0.5;
	set_direction(data, player);
	player->cam_plane = create_dvec(0.66 * fabs(player->dir.y), 0.66 *
		fabs(player->dir.x));
	data->map[line_character(data)][col_character(data)] = '0';
	data->player = player;
	data->spr.buff = malloc(sizeof(double) * data->resx);
	draw_screen(data, player);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_released, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, close_window, data);
	mlx_loop_hook(data->mlx_ptr, loop_manager, data);
	mlx_loop(data->mlx_ptr);
}

void	set_direction(t_data *data, t_player *player)
{
	if (data->dir1 == 'N')
		player->dir = create_dvec(0, -1);
	else if (data->dir1 == 'S')
		player->dir = create_dvec(0, 1);
	else if (data->dir1 == 'E')
		player->dir = create_dvec(1, 0);
	else if (data->dir1 == 'W')
		player->dir = create_dvec(-1, 0);
}

void	calculations_ray(t_player *player, int x, int resx)
{
	player->camerax = 2 * x / (double)resx - 1;
	player->ray_dir.x = player->dir.x + player->cam_plane.x * player->camerax;
	player->ray_dir.y = player->dir.y + player->cam_plane.y * player->camerax;
	player->map.x = (int)player->pos.x;
	player->map.y = (int)player->pos.y;
	player->delta_dist.x = sqrt(1 + (pow(player->ray_dir.y, 2) /
		pow(player->ray_dir.x, 2)));
	player->delta_dist.y = sqrt(1 + (pow(player->ray_dir.x, 2) /
		pow(player->ray_dir.y, 2)));
	player->hit = 0;
	player->side = 0;
	player->step = create_ivec(0, 0);
}

/*
** The DDA algorithm will always jump exactly one square each loop, either a
** square in the x-direction, or a square in the y-direction. If it has to go
** in the negative or positive x-direction, and the negative or positive
** y-direction will depend on the direction of the ray, and this fact will be
** stored in step.x and step.y. Those variables are always either -1 or +1.
*/

void	initial_dda(t_player *player)
{
	if (player->ray_dir.x < 0)
	{
		player->step.x = -1;
		player->side_dist.x = fabs((player->pos.x - player->map.x) *
			player->delta_dist.x);
	}
	else
	{
		player->step.x = 1;
		player->side_dist.x = fabs((player->map.x + 1.0 - player->pos.x) *
			player->delta_dist.x);
	}
	if (player->ray_dir.y < 0)
	{
		player->step.y = -1;
		player->side_dist.y = fabs((player->pos.y - player->map.y) *
			player->delta_dist.y);
	}
	else
	{
		player->step.y = 1;
		player->side_dist.y = fabs((player->map.y + 1.0 - player->pos.y) *
			player->delta_dist.y);
	}
}

void	dda(t_player *player, t_data *data)
{
	while (player->hit == 0)
	{
		if (player->side_dist.x <= player->side_dist.y)
		{
			player->side_dist.x += player->delta_dist.x;
			player->map.x += player->step.x;
			player->side = 0;
		}
		else
		{
			player->side_dist.y += player->delta_dist.y;
			player->map.y += player->step.y;
			player->side = 1;
		}
		if (data->map[player->map.y][player->map.x] == '1')
			player->hit = 1;
	}
}
