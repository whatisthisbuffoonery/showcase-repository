/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 15:07:40 by achew             #+#    #+#             */
/*   Updated: 2026/08/22 15:07:53 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

void	msg_exit(char *msg, t_rt *rt)
{
	if (rt && rt->fd >= 0)
		close_fd(&rt->fd, rt);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (rt)
		free_rt(rt);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *msg, t_rt *rt)
{
	if (rt && rt->fd >= 0)
		close_fd(&rt->fd, rt);
	ft_putstr_fd("Error\n", 2);
	perror(msg);
	if (rt)
		free_rt(rt);
	exit(EXIT_FAILURE);
}
