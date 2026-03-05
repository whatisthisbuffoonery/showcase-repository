/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:19:07 by dthoo             #+#    #+#             */
/*   Updated: 2026/02/19 16:19:07 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

int	ffd_heredoc(char **v, int *i, int *pfd, pid_t **cpid)
{
	(void) cpid;
	(void) v;
	(void) i;
	(void) pfd;
	return (0);
}

int	heredoc_cond(char **v)
{
	(void) v;
	return (0);
}

int	pipex_arg(int c)
{
	return ((c != 5));
}
