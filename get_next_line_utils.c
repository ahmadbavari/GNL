/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahobeida <ahobeida@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 08:37:55 by ahobeida          #+#    #+#             */
/*   Updated: 2026/09/30 09:51:44 by ahobeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
		i++;
	return (i);
}

char	*join(char *stash, char *buffer)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*res;

	len1 = ft_strlen(stash);
	len2 = ft_strlen(buffer);
	res = malloc(len1 + len2 + 1);
	if (!res)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (i < len1)
	{
		res[i] = stash[i];
		i++;
	}
	j = 0;
	while (j < len2)
		res[i++] = buffer[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if ((char)c == '\0')
		return (s);
	return (NULL);
}
