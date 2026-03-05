#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		i ++;
	write(1, a, i);
}

void	ft_putnbr(int n)
{
	int		t;
	char	a;

	t = 1;
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + '0';
		write(1, &a, 1);
		t /= 10;
	}
}

static void	permun_print(char *val, char *buf, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		buf[(unsigned char) val[i]] = i;
		i ++;
	}
	i = 0;
	while (i < max)
	{
		ft_putnbr(buf[i + 1]);
		if (i + 1 < max)
			ft_putstr(" ");
		buf[i + 1] = 0;
		i ++;
	}
	ft_putstr("\n");
}

static void	permutations(char *val, int max, int depth, char *buf)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (!val[i])
		{
			val[i] = depth;
			if (depth == max)
				permun_print(val, buf, max);
			else
				permutations(val, max, depth + 1, buf);
			val[i] = 0;
		}
		i ++;
	}
}

void	ft_print_permun(int n)
{
	int		i;
	char	*val;
	char	*buf;

	if (n < 1)
		return ;
	val = malloc((n + 2) * sizeof(char));
	buf = malloc((n + 2) * sizeof(char));
	if (!val || !buf)
	{
		free(val);
		free(buf);
		return ;
	}
	i = 0;
	while (i < n + 2)
	{
		val[i] = 0;
		buf[i] = 0;
		i ++;
	}
	permutations(val, n, 1, buf);
	free(val);
	free(buf);
}

int main(void)
{
	ft_print_permun(5);
}
