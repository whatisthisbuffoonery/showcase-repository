/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:46:43 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 20:08:54 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

int	puthex_p(uintptr_t n, char alphacase, int write_hex)
{
	const char	*hex;
	char		buf[2 * sizeof(uintptr_t)];
	int			i;

	if (alphacase == 'u')
		hex = HEX_U;
	else
		hex = HEX_L;
	if (n == 0)
		return (ft_putchar('0', write_hex));
	i = sizeof(buf);
	while (n > 0 && i > 0)
	{
		buf[--i] = hex[n & 0xF];
		n >>= 4;
	}
	if (write_hex)
		write(1, buf + i, sizeof(buf) - i);
	return ((int)(sizeof(buf) - i));
}

int	puthex_u(unsigned int n, char alphacase, int write_hex, t_arg *arg)
{
	const char	*hex;
	char		buf[2 * sizeof(uintptr_t)];
	int			len;
	int			i;

	len = 0;
	if (arg)
		len += add_zero(arg, write_hex, 0);
	if (arg && n == 0 && arg->precision == 0)
		return (len);
	if (alphacase == 'u')
		hex = HEX_U;
	else
		hex = HEX_L;
	if (n == 0)
		return (ft_putchar('0', write_hex) + len);
	i = sizeof(buf);
	while (n > 0 && i > 0)
	{
		buf[--i] = hex[n & 0xF];
		n >>= 4;
	}
	if (write_hex)
		write(1, buf + i, sizeof(buf) - i);
	return ((int)(sizeof(buf) - i) + len);
}
