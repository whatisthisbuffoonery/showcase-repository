/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:46 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:46 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	unset(int *fd)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	pipeset_cleanup(t_pipeset *set, size_t n)
{
	size_t	i;

	if (!set)
		return ;
	i = 0;
	while (i < n)
	{
		unset(&set[i][0]);
		unset(&set[i][1]);
		i ++;
	}
	free(set);
}

void	pipemanager_init(t_pipemanager *dst, int p_index)
{
	t_pipeset	*set;
	int			i;

	i = 0;
	set = malloc((p_index + 1) * sizeof(t_pipeset));
	while (i < p_index)
	{
		if (ft_err(-!set, "pipemanager malloc")
			|| ft_err(pipe(set[i]), "pipe error"))
		{
			pipeset_cleanup(set, i);
			return ;
		}
		i ++;
	}
	set[i][0] = -1;
	set[i][1] = -1;
	dst->pipes = set;
	dst->pid = 0;
	dst->pid_count = 0;
	dst->pipe_count = p_index;
}
