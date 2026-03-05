/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:36:51 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/01 14:36:52 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	fd_cleanup(int **pfd_src, int *ffd, char **v)
{
	int	i;
	int	len;
	int	*pfd;

	pfd = *pfd_src;
	if (!pfd)
		return ;
	len = pfd_len(v);
	i = 0;
	while (ffd && *ffd > 2 && i < len)
	{
		if (*ffd == pfd[i])
			*ffd = -1;
		i ++;
	}
	i = 0;
	while (i < len)
		unset(&pfd[i++]);
	if (ffd)
		unset(ffd);
	free(pfd);
	*pfd_src = NULL;
}

int	cmd_cleanup(char ***cmd)
{
	int	i;

	i = 0;
	if (*cmd)
	{
		while ((*cmd)[i])
			free((*cmd)[i++]);
		free(*cmd);
		*cmd = NULL;
	}
	return (1);
}
