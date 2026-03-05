/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabler_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:16 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 18:55:01 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	tabler(char *type, char *flag, int *a, int *b)
{
	*a = 0;
	*b = 0;
	ft_memset(type, 0, 256);
	ft_memset(flag, 0, 256);
	type['c'] = 1;
	type['s'] = 1;
	type['p'] = 1;
	type['d'] = 1;
	type['i'] = 1;
	type['u'] = 1;
	type['x'] = 1;
	type['X'] = 1;
	type['%'] = 1;
	flag['-'] = 1;
	flag['0'] = 1;
	flag['+'] = 1;
	flag[' '] = 1;
	flag['#'] = 1;
}
//. and % left out
