/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:55:12 by marvin            #+#    #+#             */
/*   Updated: 2020/09/09 20:46:52 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Hay que ver que lines esté bien si añado saltos de línea al final
*/

int		main(int argc, char **argv)
{
	int		fd;
	char	*str;
	char	*aux;
	char	*aux2;

	fd = initial_checks(argc, argv);
	while (get_next_line(fd, &str))
	{
		if (!aux)
		{
			aux = ft_strdup(str);
			free(str);
		}
		else
		{
			aux2 = ft_strjoin(aux, str);
			free(aux);
			aux = ft_strjoin(aux2, "\n");
			free(aux2);
			free(str);
		}
	}
	ft_readfile(aux, argc, argv);
}

void	ft_readfile(char *aux, int argc, char **argv)
{
	t_data	*data;
	int		j;
	int		i;

	i = 7;
	if (!(data = malloc(sizeof(t_data))))
		return ;
	data->save = 0;
	if (argc == 3)
	{
		data->save = 1;
		data->save_str = argv[2];
	}
	data->tex_w = TEX_W;
	data->tex_h = TEX_H;
	initialize_keys(data);
	data->mlx_ptr = mlx_init();
	j = get_data(aux, data, i);
	if (data->info != 8)
		exit_program_data(data, 1);
	allocate_map(data, j, aux);
}

int		get_data(char *aux, t_data *data, int i)
{
	int		j;

	j = 0;
	while (i > 0)
	{
		if (aux[j] == 'R')
			j = ft_resolution(aux, j + 1, data);
		if (aux[j] == 'F')
			j = ft_floorcol(aux, j + 1, data);
		if (aux[j] == 'C')
			j = ft_ceilcol(aux, j + 1, data);
		if (aux[j] == 'N' && aux[j + 1] == 'O')
			j = ft_northtex(aux, j + 2, data);
		if (aux[j] == 'S' && aux[j + 1] == 'O')
			j = ft_southtex(aux, j + 2, data);
		if (aux[j] == 'E' && aux[j + 1] == 'A')
			j = ft_easttex(aux, j + 2, data);
		if (aux[j] == 'W' && aux[j + 1] == 'E')
			j = ft_westtex(aux, j + 2, data);
		if (aux[j] == 'S' && aux[j + 1] != 'O')
			j = ft_sprtex(aux, j + 1, data);
		i--;
	}
	return (j);
}
