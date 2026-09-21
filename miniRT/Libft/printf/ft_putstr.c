/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:46:43 by achew             #+#    #+#             */
/*   Updated: 2025/12/17 19:27:31 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

static int	put_truncated(char *str, int write_str, t_arg *arg)
{
	int	j;

	j = 0;
	while (str[j] != '\0' && j < arg->precision)
	{
		if (write_str)
			write(1, &str[j], 1);
		j++;
	}
	return (j);
}

int	ft_putstr(char *str, int write_str, t_arg *arg)
{
	int	i;

	if (!str)
	{
		if (write_str)
			write(1, "(null)", 6);
		return (6);
	}
	if (arg && arg->precision >= 0)
		return (put_truncated(str, write_str, arg));
	else
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (write_str)
				write(1, &str[i], 1);
			i++;
		}
	}
	return (i);
}
/*
int	main(void)
{
	char *ptr;
	ptr = "hello. my name is ai ni.";
	ft_putstr(ptr);
	return (0);
}
*/	
