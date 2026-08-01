/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:31:32 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:31:33 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	path_error(char *new, int *status, int *index, int i)
{
	if (errno == ENOENT || access(new, F_OK))
		return ;
	if (!index[0])
	{
		index[0] = 1;
		index[1] = i;
		index[2] = errno;
	}
	*status = 126;
}

void	path_finish_err(char *new, char *path, char *dst, int *index)
{
	int	i;

	i = 0;
	path = &path[index[1]];
	errno = index[2];
	while (path[i] && path[i] != ':')
		i ++;
	ft_strlcpy(new, path, i + 1);
	ft_strlcat(new, "/", -1);
	ft_strlcat(new, dst, -1);
	ft_err(-1, new);
}

//calling access("dir/ + empty string", X_OK) queries the dir itself
//can return 0, not gud
int	empty_path(char *dst, char *new, int *status, int *index)
{
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	if (dst[0] && ft_strcmp(dst, ".") && ft_strcmp(dst, ".."))
		return (0);
	free(new);
	*status = ENOENT;
	return (1);
}

int	check_path(char *dst, char *new, char *path, int k)
{
	ft_strlcpy(new, path, k);
	ft_strlcat(new, "/", -1);
	ft_strlcat(new, dst, -1);
	return (!access(new, X_OK));
}

void	find_path(char *path, char **dst, char *new, int *status)
{
	int	i;
	int	k;
	int	index[3];

	i = 0;
	if (empty_path(*dst, new, status, index))
		return ;
	while (path[i])
	{
		k = 0;
		while (path[i + k] && path[i + k] != ':')
			k ++;
		if (check_path(*dst, new, &path[i], k + 1))
		{
			*status = 0;
			free(*dst);
			*dst = new;
			return ;
		}
		path_error(new, status, index, i);
		i += k + (path[i + k] != '\0');
	}
	if (*status == 126)
		path_finish_err(new, path, *dst, index);
	free(new);
}
