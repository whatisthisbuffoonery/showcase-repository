/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:18:15 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 16:18:19 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	child_wait(pid_t cpid)
{
	int		n;
	pid_t	w_return;

	errno = 0;
	w_return = waitpid(cpid, &n, 0);
	while (errno == EINTR && w_return < 0)
		w_return = waitpid(cpid, &n, 0);
	if (w_return >= 0)
		return (WEXITSTATUS(n));
	return (w_return);
}
//no logic check for waitpid

void	child_err(char **cmd, char **v, int **pfd, int *ffd)
{
	if (pfd)
		fd_cleanup(pfd, ffd, v);
	cmd_cleanup(&cmd);
	if (errno == EACCES || errno == ENOEXEC)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}
