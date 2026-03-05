void	ht_init(char *ht, char *src)
{
	int	i;

	i = 0;
	while (i < 256)
		ht[i++] = 0;
	i = 0;
	while (src[i])
		ht[(unsigned char) src[i++]] = 1;
}
