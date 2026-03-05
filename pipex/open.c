/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:19:16 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 16:19:16 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	ffd_start(char **v, int *i)
{
	int	newfd;

	errno = 0;
	newfd = open(v[1], O_RDONLY);
	while (newfd < 0 && errno == EINTR)
		newfd = open(v[1], O_RDONLY);
	*i += 1;
	return (err(newfd, "open error"));
}

//!!pipex uses > TRUNC without heredoc and >> no TRUNC with heredoc

int	ffd_end(char *v, int heredoc_flag)
{
	int	newfd;
	int	flag;

	errno = 0;
	if (heredoc_flag)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	newfd = open(v, flag, 0666);
	while (newfd < 0 && errno == EINTR)
		newfd = open(v, flag, 0666);
	return (err(newfd, "open error"));
}
