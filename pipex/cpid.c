/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:36:47 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/01 14:36:48 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	cpid_add(pid_t *dst, pid_t src, int *index, char **v)
{
	dst[*index - (3 + heredoc_cond(v))] = src;
}

int	cpid_nuke(pid_t **cpid)
{
	free(*cpid);
	*cpid = NULL;
	return (-1);
}

int	cpid_status(pid_t *cpid, char **v, int index)
{
	int	i;
	int	n;

	if (!cpid)
		return (1);
	i = 0;
	index -= 2 + heredoc_cond(v);
	while (i < index)
	{
		n = child_wait(cpid[i++]);
	}
	free(cpid);
	return (n);
}
