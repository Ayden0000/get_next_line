#include <unistd.h>
#include "get_next_line.h"

char *read_from_file(int fd, char *buffer)
{

}

char *get_next_line(int fd)
{
    char *buffer;
    int  read_size;
    int buffer_size;

    buffer_size = 3;
    static int count = 1;
    printf("ft_calloc#[%d]---", count++);
    buffer = ft_calloc(buffer_size + 1,  sizeof(char));
    read_size = read(fd, buffer, buffer_size);
    if(read_size <= 0)
        return (free(buffer),NULL);
    return (buffer);
}