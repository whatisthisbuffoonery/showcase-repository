/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:36:55 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/01 14:36:58 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_pipex.h"

void	puterr(char *a)
{
	int	i;

	i = 0;
	if (a)
	{
		while (a[i] && a[i] != ' ')
			i ++;
		write(2, a, i);
		write(2, ": ", 2);
	}
}

int	oops_err(int n, char *str)
{
	if (n < 0)
		write(2, "pipex: ", 7);
	return (cmd_err(n, str));
}

int	cmd_err(int n, char *str)
{
	if (n < 0)
	{
		if (errno != ENOENT || cmd_strchr(str))
		{
			puterr(str);
			perror(NULL);
		}
		else
		{
			puterr(str);
			write(2, "command not found\n", 18);
		}
	}
	return (n);
}

int	err(int n, char *str)
{
	if (n < 0)
	{
		write(2, "pipex: ", 7);
		perror(str);
	}
	return (n);
}

int	one_off_err(char *str)
{
	write(2, "pipex: ", 7);
	if (errno)
		perror(str);
	else
	{
		ft_putstr_fd(str, 2);
		write(2, ": unclosed quotes\n", 18);
	}
	return (-1);
}
