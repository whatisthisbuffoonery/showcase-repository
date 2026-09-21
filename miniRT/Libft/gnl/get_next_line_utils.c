/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:21:14 by achew             #+#    #+#             */
/*   Updated: 2026/02/01 14:34:21 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*b1;
	const unsigned char	*b2;

	b1 = (const unsigned char *)s1;
	b2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while ((i < n) && (b1[i] == b2[i]))
		i++;
	if (i == n)
		return (0);
	return (b1[i] - b2[i]);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ch;
	const unsigned char	*src_ch;

	dest_ch = (unsigned char *)dest;
	src_ch = (const unsigned char *)src;
	if (n == 0 || dest_ch == src_ch)
		return (dest);
	if (dest_ch < src_ch)
	{
		while (n--)
			*dest_ch++ = *src_ch++;
	}
	else
	{
		dest_ch += n;
		src_ch += n;
		while (n--)
			*--dest_ch = *--src_ch;
	}
	return (dest);
}

char	*init_array(int size)
{
	char	*buffer;

	if (size <= 0)
		return (NULL);
	buffer = malloc((size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ft_memset2(buffer, '\0', size + 1);
	return (buffer);
}

ssize_t	fill_buffer(char *buffer, int fd, char *stash)
{
	ssize_t	buffer_len;
	char	null[BUFFER_SIZE + 1];

	ft_memset2(null, '\0', BUFFER_SIZE + 1);
	if (ft_memcmp(stash, null, BUFFER_SIZE + 1) == 0)
		buffer_len = read(fd, buffer, BUFFER_SIZE);
	else
	{
		ft_memmove(buffer, stash, buffer_len = ft_strlen2(stash));
		ft_memset2(stash, '\0', BUFFER_SIZE + 1);
	}
	return (buffer_len);
}

ssize_t	get_line_len(char *buffer, ssize_t buffer_len)
{
	int	i;

	if (buffer_len <= 0)
		return (0);
	i = 0;
	while (i < buffer_len && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}
