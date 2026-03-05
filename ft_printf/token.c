/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:27 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 19:27:45 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	tabler(char *type, char *flag, int *a, int *b);
t_queue	*new_op(const char *format, int *index, char *type);
t_queue	*new_str(const char *format, int start, int *end);
int		valid_cond_printf(const char *format, char *type, char *flag, int *i);

static int	valid(const char *format, int size, char *type, char *flag)
{
	int	i;

	i = 0;
	if (!format || !format[0] || size <= 0)
		return (0);
	if (size == 1 && format[0] == '%')
		return (0);
	while (i + 1 < size)
	{
		if (format[i] == '%')
		{
			i ++;
			if (!valid_cond_printf(format, type, flag, &i))
				return (0);
		}
		i ++;
	}
	return (1);
}

void	printf_tokens(const char *format, t_queue **q, int size)
{
	int		i;
	int		start;
	char	type[256];
	char	flag[256];
	t_queue	*tmp;

	tabler(type, flag, &i, &start);
	if (!valid(format, size, type, flag))
		return ;
	while (i < size)
	{
		while (i < size && format[i] != '%')
			i ++;
		if (format[start] == '%' && format[start + 1] != '%')
			tmp = new_op(&format[i], &i, type);
		else if (format[start])
			tmp = new_str(format, start, &i);
		if (enq(q, tmp))
			return ;
		start = i;
	}
}
