/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 18:40:30 by isfernan          #+#    #+#             */
/*   Updated: 2020/09/09 20:05:01 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_resolution(char *aux, int i, t_data *data)
{
	i = skip_spaces(aux, i);
	data->resx = ft_atoi(aux + i);
	while (ft_isdigit(aux[i]))
		i++;
	i = skip_spaces(aux, i);
	data->resy = ft_atoi(aux + i);
	while (ft_isdigit(aux[i]) || aux[i] == ' ' || aux[i] == '\n')
		i++;
	if (data->resx > 2560)
		data->resx = 2560;
	if (data->resy > 1440)
		data->resy = 1440;
	data->info++;
	return (i);
}

int		ft_floorcol(char *aux, int i, t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	i = skip_spaces(aux, i);
	data->floor.r = ft_atoi(aux + i);
	i = i + count_nb(data->floor.r);
	i = skip_spa_com(aux, i);
	data->floor.g = ft_atoi(aux + i);
	i = i + count_nb(data->floor.g);
	i = skip_spa_com(aux, i);
	data->floor.b = ft_atoi(aux + i);
	while (ft_isdigit(aux[i]) || aux[i] == ' ' || aux[i] == '\n')
		i++;
	str1 = to_base(data->floor.r);
	str2 = to_base(data->floor.g);
	str3 = to_base(data->floor.b);
	str4 = ft_strjoin(str2, str3);
	data->f_c = number_base(ft_strjoin(str1, str4));
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	data->info++;
	return (i);
}

int		ft_ceilcol(char *aux, int i, t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	i = skip_spaces(aux, i);
	data->ceil.r = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.r);
	i = skip_spa_com(aux, i);
	data->ceil.g = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.g);
	i = skip_spa_com(aux, i);
	data->ceil.b = ft_atoi(aux + i);
	i = i + count_nb(data->ceil.b);
	while(aux[i] == '\n')
		i++;
	data->ceil_col = ft_strjoin((str1 = to_base(data->ceil.r)),
			(str2 = ft_strjoin((str4 = to_base(data->ceil.g)), (str3 = to_base(data->ceil.b)))));
	data->c_c = number_base(data->ceil_col);
	data->info++;
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	if (!(check_colors(data)))
		exit_program_data(data, 2);
	return (i);
}

int		ft_northtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	if ((data->texture[TEX_N].path = ft_getpath(aux, i, icpy)))
	{
		while (aux[icpy] == '\n')
			icpy++;
		if ((data->texture[TEX_N].texim.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[TEX_N].path, &data->tex_w, &data->tex_h)))
			data->texture[TEX_N].texim.addr = mlx_get_data_addr
			(data->texture[TEX_N].texim.img, &data->texture[TEX_N].texim.bits_per_pixel,
			&data->texture[TEX_N].texim.line_length, &data->texture[TEX_N].texim.endian);
		else
			exit_program_data(data, 3);
	}
	data->info++;
	return (icpy);
}

int		ft_southtex(char *aux, int i, t_data *data)
{
	int		icpy;

	i = skip_spaces(aux, i);
	icpy = i;
	while (!ft_isspace(aux[icpy]))
		icpy++;
	if ((data->texture[TEX_S].path = ft_getpath(aux, i, icpy)))
	{
		while (aux[icpy] == '\n')
			icpy++;
		if ((data->texture[TEX_S].texim.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->texture[TEX_S].path, &data->tex_w, &data->tex_h)))
			data->texture[TEX_S].texim.addr = mlx_get_data_addr
			(data->texture[TEX_S].texim.img, &data->texture[TEX_S].texim.bits_per_pixel,
			&data->texture[TEX_S].texim.line_length, &data->texture[TEX_S].texim.endian);
		else
			exit_program_data(data, 3);
	}
	data->info++;
	return (icpy);
}
