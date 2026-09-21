/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:46:43 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 14:55:43 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

int	putptr(void *ptr, int write_ptr, t_arg *arg)
{
	uintptr_t	addr;
	int			len;

	if (!ptr)
	{
		if (write_ptr)
			write(1, "(nil)", 5);
		return (5);
	}
	len = 0;
	if (write_ptr)
		write(1, "0x", 2);
	if (arg)
		len += add_zero(arg, write_ptr, 0);
	addr = (uintptr_t)ptr;
	len += puthex_p(addr, 'l', write_ptr);
	return (len + 2);
}
