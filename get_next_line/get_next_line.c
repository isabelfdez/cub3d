/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:40:42 by isfernan          #+#    #+#             */
/*   Updated: 2020/03/10 13:22:01 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 2

void		ft_gnl(char *buff[], char **line, int *nb, int fd)
{
	char		*aux;
	char		*buffcpy;
	int			nl;

	nl = ft_strchr2(buff[fd], '\n');
	if (nl != -1)
	{
		*nb = 1;
		aux = malloc(sizeof(char) * nl + 1);
		ft_memcpy(aux, buff[fd], nl);
		aux[nl] = 0;
		*line = ft_strdup(aux);
		free(aux);
		buffcpy = ft_strdup(buff[fd]);
		free(buff[fd]);
		buff[fd] = ft_strdup(buffcpy + nl + 1);
		free(buffcpy);
	}
	else
	{
		*line = ft_strdup(buff[fd]);
		free(buff[fd]);
		buff[fd] = NULL;
	}
}

int			ft_read(int fd, char str[], char *buff[])
{
	char		*aux;
	int			nb;

	while ((nb = read(fd, str, BUFFER_SIZE)) > 0)
	{
		str[nb] = 0;
		if (!buff[fd])
			buff[fd] = ft_strdup(str);
		else
		{
			aux = ft_strjoin(buff[fd], str);
			free(buff[fd]);
			buff[fd] = aux;
		}
		if (ft_strchr2(buff[fd], '\n') != -1)
			break ;
	}
	return (nb);
}

int			get_next_line(int fd, char **line)
{
	static char	*buff[4096];
	char		str[BUFFER_SIZE + 1];
	int			nb;

	nb = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || fd >= 4096)
		return (-1);
	if (!buff[fd] || (ft_strchr2(buff[fd], '\n')) == -1)
		nb = ft_read(fd, str, buff);
	if (!(nb) && !buff[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (nb < 0)
		return (-1);
	ft_gnl(buff, line, &nb, fd);
	return (nb);
}
