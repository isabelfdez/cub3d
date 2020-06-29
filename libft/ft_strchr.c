/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isfernan <isfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:58:04 by isfernan          #+#    #+#             */
/*   Updated: 2020/03/10 13:36:23 by isfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*ptr;

	i = 0;
	ch = c;
	while (s[i])
	{
		if (s[i] == ch)
		{
			ptr = (char *)s + i;
			return (ptr);
		}
		i++;
	}
	if (ch == s[i])
	{
		ptr = (char *)s + i;
		return (ptr);
	}
	return (NULL);
}

/*
** This function is the same as ft_strchr but it returns
** the index of the character searched. If not found, it
** return (-1)
*/

int		ft_strchr2(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (ch == s[i])
		return (i);
	return (-1);
}

