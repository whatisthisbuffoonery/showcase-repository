/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:19:05 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 16:19:05 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

//2 on match, 1 otherwise
int	heredoc_cond(char **v)
{
	static int	flag;

	if (!flag)
		flag = !ft_strcmp(v[1], "here_doc") + 1;
	(void) v;
	return (flag - 1);
}

int	heredoc_write(int fd, char *line)
{
	int	written;
	int	i;
	int	len;

	written = 0;
	len = ft_strlen(line);
	while (written < len)
	{
		errno = 0;
		i = write(fd, line + written, len - written);
		if (i < 0 && errno != EINTR)
		{
			free(line);
			return (err(-1, "write error"));
		}
		if (!errno)
			written += i;
	}
	free(line);
	return (0);
}

int	pipex_cmp(char *line, char *v, int v_len)
{
	int		line_len;

	line_len = ft_strlen(line);
	if (line_len != v_len + 1 || line[v_len] != '\n')
		return (1);
	return (ft_strncmp(line, v, v_len));
}

//not considering tokens (not told to accept ">>")

int	ffd_heredoc(char **v, int *i, int *pfd, pid_t **cpid)
{
	char	*line;
	int		len;

	errno = 0;
	if (*i != 1 || !heredoc_cond(v))
		return (0);
	len = ft_strlen(v[2]);
	line = gnl_b(0);
	while (line && pipex_cmp(line, v[2], len))
	{
		if (heredoc_write(pfd[1], line))
			return (cpid_nuke(cpid));
		line = gnl_b(0);
	}
	free(line);
	*i += 2;
	if (errno)
		return (err(cpid_nuke(cpid), "read error"));
	return (0);
}

int	pipex_arg(int c)
{
	return ((c < 5));
}
