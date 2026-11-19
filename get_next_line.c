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

static char    *scale_buffer(char *buffer, char *read_buffer)
{
    char *tmp;

    tmp = ft_strjoin(buffer, read_buffer);
    free(buffer);
    return (tmp);
}

static char	*read_from_file(int fd, char *buffer)
{
	int	read_size;
    char *read_buffer;

    read_buffer = ft_calloc(BUFFER_SIZE + 1 , sizeof(char));
    if(!read_buffer)
        return (NULL);
    read_size = 1;
    while (read_size > 0)
    {
        read_size = read(fd, read_buffer, BUFFER_SIZE);
        if (read_size < 0)
		    return (free(buffer), free(read_buffer), NULL);
		read_buffer[read_size] = '\0';
        buffer = scale_buffer(buffer, read_buffer);
        if(!buffer)
            return(free(read_buffer), NULL);
        if(ft_strchr(buffer, LINE_DIVIDER))
            break;
    }
    free(read_buffer);
	return (buffer);
}

static char *extract_line(char *buffer)
{
    int i;
    char *line;

    i = 0;
    if(!buffer || !buffer[0])
        return NULL;
    while (buffer[i] && buffer[i] != LINE_DIVIDER)
        i++;
    if(buffer[i] == LINE_DIVIDER)
        i++;
    line = ft_calloc(i + 1, sizeof(char));
    if(!line)
        return(NULL);
    while(i-- > 0)
        line[i] = buffer[i];
    return line;
}

static char *update_buffer(char *buffer)
{
    char *line;
    char *remaining_buf;

    if (!buffer)
        return (NULL);
    line = ft_strchr(buffer, LINE_DIVIDER);
    if(!line || !line[1])
        return(free(buffer), NULL);
    remaining_buf = ft_strjoin(NULL, line + 1);
    if (!remaining_buf) 
      return(free(buffer), NULL);
    return (free(buffer), remaining_buf);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
    char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!ft_strchr(buffer, LINE_DIVIDER))
        buffer = read_from_file(fd, buffer);
    if (!buffer)
		return (NULL);
    line = extract_line(buffer);
    if(!line)
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }
    buffer = update_buffer(buffer);
    return (line);
}
