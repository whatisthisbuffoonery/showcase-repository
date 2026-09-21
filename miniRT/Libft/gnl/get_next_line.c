/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 12:21:14 by achew             #+#    #+#             */
/*   Updated: 2026/02/05 17:26:59 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		total_len;
	char	*joined;
	int		i;
	int		m;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen2(s1) + ft_strlen2(s2);
	joined = malloc((total_len + 1) * sizeof(char));
	if (joined)
	{
		m = 0;
		i = 0;
		while (s1[m] != '\0')
			joined[i++] = s1[m++];
		m = 0;
		while (s2[m] != '\0')
			joined[i++] = s2[m++];
		joined[i] = '\0';
	}
	return (joined);
}

char	*extend_line(char *line, int fd)
{
	char	*next;
	char	*joined;

	next = get_next_line(fd);
	if (!next)
		return (line);
	joined = ft_strjoin2(line, next);
	free(line);
	free(next);
	if (!joined)
		return (NULL);
	return (joined);
}

void	*ft_memset2(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	chara;
	unsigned char	*buf;

	chara = (unsigned char)c;
	buf = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		buf[i] = chara;
		i++;
	}
	return (b);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		buffer_len;
	char		*line;
	ssize_t		line_len;
	static char	stash[1024][BUFFER_SIZE + 1];

	if (fd < 0)
		return (NULL);
	buffer = init_array(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	buffer_len = fill_buffer(buffer, fd, stash[fd]);
	line_len = get_line_len(buffer, buffer_len);
	line = init_array(line_len);
	if (buffer_len <= 0 || !line)
		return (free(buffer), NULL);
	line = ft_memmove(line, buffer, line_len);
	if (line[line_len - 1] != '\n')
		line = extend_line(line, fd);
	else
		ft_memmove(stash[fd], buffer + line_len, buffer_len - line_len);
	if (!line)
		return (NULL);
	return (free(buffer), line);
}

//int	main(int argc, char **argv)
//{
//	int		fd[argc - 1];
//	char	*result;
//	int		len;
//	int		i;
//	int		n;
//
//	if (argc > 1)
//	{
//		n = 1;
//		while (n < argc)
//		{
//			if ((strcmp(argv[n], "0") == 0))
//				fd[n] = 0;
//			else
//			{
//				fd[n] = open(argv[n], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
//			}
//			if (fd[n] == -1)
//			{
//				perror("Error opening file with open\n");
//				return (1);
//			}
//			n++;
//		}
//		i = 1;
//		
//		if (argc == 2)
//		{
//			while ((result = get_next_line(fd[1])))
//			{
//				len = ft_strlen2(result);
//				printf("%d: (%d) %s", i++, len, result);
//				free(result);
//			}
//		}
//		else
//		{
//			while (i < 11)
//			{
//				n = 1;
//				while (n < argc)
//				{
//					if ((result = get_next_line(fd[n])))
//					{
//						len = ft_strlen2(result);
//						printf("%d: (%d) %s", i, len, result);
//						free(result);
//					}
//					n++;
//				}
//				i++;
//			}
//		}
//		while (n < argc)
//			close(fd[n]);
//	}
//	return (0);
//}
