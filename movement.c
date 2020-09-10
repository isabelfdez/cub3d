/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:47:13 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/10 17:54:38 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_towards(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x + M_SPEED * player->dir.x;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x += M_SPEED * player->dir.x;
	x = player->pos.x;
	y = player->pos.y + M_SPEED * player->dir.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y += M_SPEED * player->dir.y;
}

void	move_backwards(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x - M_SPEED2 * player->dir.x;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x -= M_SPEED2 * player->dir.x;
	x = player->pos.x;
	y = player->pos.y - M_SPEED2 * player->dir.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y -= M_SPEED2 * player->dir.y;
}

void	move_right(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x - M_SPEED * player->dir.y;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x -= M_SPEED * player->dir.y;
	x = player->pos.x;
	y = player->pos.y + M_SPEED * player->dir.x;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y += M_SPEED * player->dir.x;
}

void	move_left(t_data *data)
{
	int			x;
	int			y;
	t_player	*player;

	player = data->player;
	x = player->pos.x + M_SPEED * player->dir.y;
	y = player->pos.y;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.x += M_SPEED * player->dir.y;
	x = player->pos.x;
	y = player->pos.y - M_SPEED * player->dir.x;
	if (x < data->c && y < data->l && data->map[y][x] == '0')
		data->player->pos.y -= M_SPEED * player->dir.x;
}
