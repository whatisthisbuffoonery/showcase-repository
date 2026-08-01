int	ft_ptrlen(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i ++;
	return (i);
}
