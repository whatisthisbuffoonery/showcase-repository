/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:13 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:13 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	check_flag(char *v)
{
	int	i;

	if (!v || v[0] != '-' || v[1] != 'n')
		return (0);
	i = 1;
	while (v[i] && v[i] == 'n')
		i ++;
	return (!v[i]);
}

int	echo(char **argv, int out)
{
	int	flag;
	int	i;

	flag = check_flag(argv[1]);
	i = flag + 1;
	while (argv[i])
	{
		if (!check_flag(argv[i]))
			break ;
		i ++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], out);
		if (argv[i + 1])
			ft_putchar_fd(' ', out);
		i ++;
	}
	if (!flag)
		ft_putchar_fd('\n', out);
	return (0);
}
