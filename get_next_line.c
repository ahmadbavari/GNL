/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahobeida <ahobeida@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 08:38:02 by ahobeida          #+#    #+#             */
/*   Updated: 2026/09/30 16:56:27 by ahobeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	fail_read(char **stash, char *buffer)
{
	free(*stash);
	*stash = NULL;
	free(buffer);
	return (0);
}

static int	read_stash(int fd, char **stash)
{
	char	*buffer;
	char	*new;
	int		x;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	x = 1;
	while (!ft_strchr(*stash, '\n') && x > 0)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x < 0)
			return (fail_read(stash, buffer));
		buffer[x] = '\0';
		new = join(*stash, buffer);
		if (!new)
			return (fail_read(stash, buffer));
		free(*stash);
		*stash = new;
	}
	free(buffer);
	return (1);
}

static char	*make_line(char *stash, int j)
{
	int		i;
	char	*result;

	result = malloc(j + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (i < j)
	{
		result[i] = stash[i];
		i++;
	}
	if (stash[j] == '\n')
	{
		result[i] = '\n';
		result[i + 1] = '\0';
	}
	else
		result[i] = '\0';
	return (result);
}

static char	*trim_stash(char **stash, char *result, int j)
{
	int		i;
	int		k;
	char	*new_stash;

	new_stash = NULL;
	if ((*stash)[j] == '\n')
	{
		new_stash = malloc(ft_strlen(*stash) - j);
		if (!new_stash)
		{
			free(result);
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		i = j + 1;
		k = 0;
		while ((*stash)[i])
			new_stash[k++] = (*stash)[i++];
		new_stash[k] = '\0';
	}
	free(*stash);
	*stash = new_stash;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;
	int			j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_stash(fd, &stash))
		return (NULL);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	j = 0;
	while (stash[j] && stash[j] != '\n')
		j++;
	result = make_line(stash, j);
	if (!result)
		return (NULL);
	return (trim_stash(&stash, result, j));
}
