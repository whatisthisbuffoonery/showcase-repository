/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:03 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/30 18:32:47 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*percent_op(t_pf_q *q);
char	*char_op(unsigned int c, t_pf_q *q);
char	*ptr_op(uintptr_t src, char type, t_pf_q *q, char *hex);
char	*uint_op(unsigned long n, char type, t_pf_q *q, char *hex);
char	*int_op(int n, t_pf_q *q);

static void	hex_init(char *a)
{
	a[0] = '0';
	a[1] = '1';
	a[2] = '2';
	a[3] = '3';
	a[4] = '4';
	a[5] = '5';
	a[6] = '6';
	a[7] = '7';
	a[8] = '8';
	a[9] = '9';
	a[10] = 'a';
	a[11] = 'b';
	a[12] = 'c';
	a[13] = 'd';
	a[14] = 'e';
	a[15] = 'f';
}

static char	*grab(t_pf_q *q, va_list *va, char *hex)
{
	char	cmp;

	if (q->type == str)
		return (q->str);
	else if (q->type == op)
	{
		cmp = q->arg;
		if (cmp == '%')
			return (percent_op(q));
		if (cmp == 'c')
			return (char_op(va_arg(*va, int), q));
		else if (cmp == 's' || cmp == 'p')
			return (ptr_op(va_arg(*va, uintptr_t), cmp, q, hex));
		else if (cmp == 'd' || cmp == 'i')
			return (int_op(va_arg(*va, int), q));
		else if (cmp == 'u' || cmp == 'x' || cmp == 'X')
			return (uint_op(va_arg(*va, unsigned int), cmp, q, hex));
	}
	return (NULL);
}

int	print_strlen(char *a, t_pf_q *q)
{
	int	i;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i ++;
	if (q->arg == '0')
	{
		i ++;
		while (a[i])
			i ++;
	}
	return (i);
}

int	process(t_pf_q *q, va_list *va)
{
	t_pf_q	*f;
	char	*new;
	char	hex[16];

	f = q;
	hex_init(hex);
	while (f)
	{
		new = grab(f, va, hex);
		if (!new)
			return (-1);
		f->str = new;
		f = f->next;
	}
	return (0);
}
