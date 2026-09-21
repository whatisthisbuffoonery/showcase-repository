/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:24:36 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:24:38 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

static char	*read_all_lines(char *file, t_rt *rt)
{
	char	*joined;
	char	*tmp;
	char	*line;
	int		fd;

	fd = open_fd(file, rt);
	joined = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		tmp = joined;
		joined = ft_strjoin(joined, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close_fd(&rt->fd, rt);
	return (joined);
}

static int	count_tokens(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static char	**split_tokens(char *s, int n, t_rt *rt)
{
	char	**tokens;
	int		i;
	int		j;
	int		start;

	tokens = ft_calloc(n + 1, sizeof(char *));
	if (!tokens)
		msg_exit("malloc failure", rt);
	i = 0;
	j = 0;
	while (j < n)
	{
		while (ft_isspace(s[i]))
			i++;
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		tokens[j] = ft_substr(s, start, i - start);
		if (!tokens[j])
			msg_exit("malloc failure", rt);
		j++;
	}
	return (tokens);
}

void	tokenize_file(char *file, t_rt *rt)
{
	char	*buf;
	int		n;

	buf = read_all_lines(file, rt);
	n = count_tokens(buf);
	rt->tokens = split_tokens(buf, n, rt);
	free(buf);
}
