
#include "cub3d.h"

int	read_file(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}
