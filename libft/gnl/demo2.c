#include "libft.h"
#include "get_next_line.h"

int main(int c, char **v)
{
	if (c < 3)
	{
		ft_putstr("Usage: \'./a.out [filename] [number of lines to print]\'\n");
		return (1);
	}
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("failed to open file\n", 2);
		return (1);
	}
	unsigned int lines = ft_atoi(v[2]);

	char *receive = NULL;
	while (lines)
	{
		receive = gnl(fd);
		if (!receive)
			break ;
		ft_putstr(receive);
		free(receive);
		lines --;
		receive = NULL;
	}
	close(fd);
}
