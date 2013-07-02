#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

/*
read stream from fd
return if buffer is full or if char is \n
 */

char	*get_next_line( int fd )
{
  int		i;
  char		*line;
  static char	buffer[BUFFER_SIZE];
  static int	read_pos = 0;
  static int	bytes_read = 0;

  if (read_pos == bytes_read)
    {
      read_pos = 0;
      if ((bytes_read = read(fd, buffer, BUFFER_SIZE)) == 0)
	return NULL;
    }
  if (!(line = malloc(bytes_read - read_pos + 1)))
    return NULL;
  for (i = 0; read_pos < bytes_read; read_pos++, i++)
    {
      line[i] = buffer[read_pos];
      if (buffer[read_pos] == '\n')
	{
	  read_pos++;
	  line[i + 1] = NULL;
	  return line;
	}
    }
  line[i] = NULL;
  return line;
}
