/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:31:18 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:31:19 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	main(int c, char **v, char **e)
{
	(void) c;
	if (v[1] && !ft_strcmp(v[1], "--version"))
	{
		ft_putstr("Bash-inspired minishell, version 0.67\n");
		return (0);
	}
	return (loop(e));
}
