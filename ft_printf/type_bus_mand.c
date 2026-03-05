/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bus_mand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:44 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 17:28:45 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_bus(t_queue *q, const char *format, char *type)
{
	(void) type;
	if (!q)
		return (0);
	q->arg = format[0];
	return (0);
}
