/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserrano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:32:09 by isfernan          #+#    #+#             */
/*   Updated: 2020/03/12 17:06:20 by aserrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(const char *h, const char *needle, size_t i, size_t len)
{
	size_t	c;

	c = 0;
	while (i < len && h[i])
	{
		if (!(h[i] == needle[c]))
			return (0);
		i++;
		c++;
		if (!(needle[c]))
			return (1);
	}
	if (!(needle[c]))
		return (1);
	if (needle[c] == h[i] && !(needle[c]))
		return (1);
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!(*(needle)))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_find(haystack, needle, i, len))
			{
				ptr = (char *)haystack + i;
				return (ptr);
			}
		}
		i++;
	}
	return (NULL);
}

/*
** This function does the same as strstr but returns the index
** of the pointer instead of the pointer itself.
** It returns -1 if needle is not found or if it doesn't exist.
** Also, the strings taken as arguments are not constant
*/

static int	ft_find2(const char *h, const char *needle, size_t i)
{
	int	c;

	c = 0;
	while (h[i])
	{
		if (!(h[i] == needle[c]))
			return (0);
		i++;
		c++;
		if (!(needle[c]))
			return (1);
	}
	if (!(needle[c]))
		return (1);
	if (needle[c] == h[i] && !(needle[c]))
		return (1);
	return (0);
}

int		ft_strstr2(char *haystack, char *needle)
{
	int	i;

	i = 0;
	if (!(*needle))
		return (-1);
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_find2(haystack, needle, i))
				return (i);
		}
		i++;
	}
	return (-1);
}

/*
** This function does the same as strnstr but returns NULL 
** if needle doesn't exist instead of haystack
*/

char		*ft_strnstr3(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!(*(needle)))
		return (NULL);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_find(haystack, needle, i, len))
			{
				ptr = (char *)haystack + i;
				return (ptr);
			}
		}
		i++;
	}
	return (NULL);
}