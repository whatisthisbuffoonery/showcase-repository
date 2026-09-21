/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:25:55 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:25:58 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

int	open_fd(char *file, t_rt *rt)
{
	rt->fd = open(file, O_RDONLY, 0444);
	if (rt->fd < 0)
		perror_exit(file, rt);
	return (rt->fd);
}

void	close_fd(int *fd, t_rt *rt)
{
	if (*fd >= 0 && close(*fd) == -1)
		perror_exit("closing of fd", rt);
	*fd = -1;
}
