#include "get_next_line.h"
#include "../includes/libft.h"

int main(int c, char **v)
{
	if (c < 3)
	{
		ft_putstr("Usage: \'./a.out [filename] [which line to print]\'\n");
		return (1);
	}
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return ((write(1, "no open\n", 8)), 1);
	unsigned int line = ft_atoi(v[2]);
	char *receive = NULL;
	while (line)
	{
		receive = get_next_line(fd);
		if (receive == NULL)
			return ((close(fd)), 0);
		line --;
		if (!line)
			break ;
		free(receive);
	}
	ft_putstr(receive);
	free(receive);
	close(fd);
}
