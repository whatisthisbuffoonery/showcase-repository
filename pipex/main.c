/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:19:10 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 18:54:17 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	pfd_len(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i ++;
	return ((i - (1 + heredoc_cond(v))) * 2);
}

int	pfd_init(char **v, int **pfd)
{
	int	len;
	int	i;

	len = pfd_len(v);
	*pfd = malloc(len * sizeof(int));
	if (!*pfd)
		return (err(-1, "malloc error"));
	i = 0;
	while (i < len)
		(*pfd)[i++] = 0;
	i = 0;
	while (i < len)
	{
		if (err(pipe(&(*pfd)[i]), "pipe error"))
		{
			fd_cleanup(pfd, NULL, v);
			return (1);
		}
		i += 2;
	}
	return (0);
}

int	main_init(int *index, char **v, int **pfd, pid_t **cpid)
{
	int	i;
	int	k;

	i = 0;
	while (v[i])
		i ++;
	if (pipex_arg(i) || pfd_init(v, pfd))
		return (1);
	i -= 2 + heredoc_cond(v);
	*cpid = malloc(i * sizeof(pid_t));
	if (!*cpid)
	{
		fd_cleanup(pfd, NULL, v);
		return (1);
	}
	k = 0;
	while (k < i)
		(*cpid)[k++] = 0;
	*index = 1;
	return (0);
}
/*
int	main_wait(int *pfd, int i, char **v)
{
	int	index;

	i --;
	index = pfd_grab(i, v);
	unset(&pfd[index + 1]);
	return (child_wait());
}
*/
//for basic pipe, c == 5 and last file == 4

pid_t	fork_wrap(pid_t *tmp, int *i)
{
	pid_t	result;

	result = fork();
	if (result > 0)
	{
		if (*i == 1)
			*i += 1;
		*i += 1;
	}
	*tmp = result;
	return (err((result > 0) - (result < 0), "fork error"));
}

int	main(int c, char **v, char **e)
{
	int		i;
	int		*pfd;
	pid_t	tmp;
	pid_t	*cpid;

	if (main_init(&i, v, &pfd, &cpid))
		return (1);
	while (i < c - 1)
	{
		if (!ffd_heredoc(v, &i, pfd, &cpid))
		{
			if (fork_wrap(&tmp, &i) == 0)
			{
				cpid_nuke(&cpid);
				fork_handler(v, &i, pfd, e);
			}
		}
		if (!cpid || tmp < 1)
			break ;
		cpid_add(cpid, tmp, &i, v);
	}
	fd_cleanup(&pfd, NULL, v);
	return (cpid_status(cpid, v, i));
}
//actually get the last command and not get caught on a partial cpid situation
