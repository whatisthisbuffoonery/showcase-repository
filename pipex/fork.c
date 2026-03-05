/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:18:58 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 18:54:50 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

//this is apparently the error msg, nobody can make up their minds what it is

int	std_dup(int *pfd, int *ffd, int i, char **v)
{
	int	fd;

	fd = pfd[0];
	if (*ffd > 2 && i < 3 + heredoc_cond(v))
	{
		fd = *ffd;
	}
	if (dup2(fd, 0) < 0)
		return (err(-1, "cannot duplicate fd"));
	fd = pfd[3];
	if (*ffd > 2 && !v[i + 2])
	{
		fd = *ffd;
	}
	if (dup2(fd, 1) < 0)
	{
		close(0);
		return (err(-1, "cannot duplicate fd"));
	}
	return (0);
}

int	ffd_init(char **v, int *i, int **pfd, int *ffd)
{
	*ffd = 0;
	errno = 0;
	if (*i == 1 && !heredoc_cond(v))
	{
		*ffd = ffd_start(v, i);
	}
	else if (!v[*i + 2])
		*ffd = ffd_end(v[*i + 1], heredoc_cond(v));
	if (*ffd < 0)
	{
		fd_cleanup(pfd, ffd, v);
		return (1);
	}
	return (0);
}

//one for infile, one for argv[0]

int	pfd_grab(int i, char **v)
{
	return (2 * (i - (1 + 1 + heredoc_cond(v))));
}

//i value without heredoc: 2, 3, 4, 5, ...
//with: 3, 4, 5, 6, ...

void	fork_handler(char **v, int *i, int *pfd_src, char **e)
{
	char	**cmd;
	int		*pfd;
	int		ffd;

	if (ffd_init(v, i, &pfd_src, &ffd))
		exit(1);
	pfd = &pfd_src[pfd_grab(*i, v)];
	if (cmd_init(v, i, &cmd, e) || std_dup(pfd, &ffd, *i, v))
		child_err(cmd, v, &pfd_src, &ffd);
	fd_cleanup(&pfd_src, &ffd, v);
	execve(cmd[0], cmd, e);
	cmd_err(-1, cmd[0]);
	close(0);
	close(1);
	child_err(cmd, NULL, NULL, NULL);
}
