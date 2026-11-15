/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nychan <nychan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 18:03:51 by nychan            #+#    #+#             */
/*   Updated: 2026/11/15 19:07:19 by nychan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*read_from_file(int fd, char *buffer)
{
	int	read_size;

	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size <= 0)
		return (free(buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(buffer), NULL);
	if (!ft_strchr(buffer, LINE_DIVIDER))
        buffer = read_from_file(fd, buffer);
    if (!buffer)
		return (free(buffer), NULL);
    
}
