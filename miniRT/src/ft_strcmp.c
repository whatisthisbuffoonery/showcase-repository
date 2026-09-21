int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i ++;
	return ((unsigned char) a[i] - (unsigned char) b[i]);
}
