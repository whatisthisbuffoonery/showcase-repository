/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:28:36 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 16:22:19 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	ap;
	int		*fmt_len;
	t_arg	*arg;

	len = 0;
	va_start(ap, str);
	while (*str)
	{
		fmt_len = is_fmt(str);
		if (fmt_len)
		{
			arg = init_arg(str, fmt_len, ap);
			len += print_data(arg);
			str += fmt_len[0];
			free(fmt_len);
			free(arg);
		}
		else
			len += ft_putchar(*str, 1);
		str++;
	}
	va_end(ap);
	return (len);
}
