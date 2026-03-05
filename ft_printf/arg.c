/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 01:08:20 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/30 18:31:57 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		uint_init(int *i, unsigned long *t);
int		uint_help(char *ret, int flag, t_queue *q, int *i);
int		int_help(char *ret, int flag, t_queue *q, int *index);
int		prec_help(char *ret, t_queue *q, int n, int index);
int		str_min(char **s, int size, t_queue *q);
char	*handle_flag(size_t size, t_queue *q, int *index);

char	*percent_op(t_queue *q)
{
	char	*ret;
	int		i;

	if (q && q->flags)
	{
		free(q->flags);
		q->flags = NULL;
	}
	ret = handle_flag(1 * sizeof(char), q, &i);
	if (ret)
		ret[i] = '%';
	return (ret);
}

char	*char_op(unsigned int c, t_queue *q)
{
	char	*ret;
	int		i;

	i = 0;
	ret = handle_flag(1 * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	ret[i] = c;
	if (!c)
		q->arg = '0';
	return (ret);
}

char	*uint_op(unsigned long n, char type, t_queue *q, char *hex)
{
	char			*ret;
	int				i;
	int				flag;
	unsigned long	t;
	unsigned int	base;

	base = uint_init(&i, &t) - (6 * (type == 'u'));
	while (n / t >= base && ++i)
		t *= base;
	if (!n && q->flags)
		q->flags->hex = 0;
	flag = 2 * (type == 'p' || (q->flags && q->flags->hex));
	ret = handle_flag((i + flag) * sizeof(char), q, &i);
	if (uint_help(ret, flag, q, &i) || prec_help(ret, q, (n != 0), i))
		return (ret);
	while (t)
	{
		ret[i] = hex[((n / t) % base)];
		if (type == 'X' && ret[i] > '9')
			ret[i] -= 32;
		i ++;
		t /= base;
	}
	return (ret);
}

char	*int_op(int num, t_queue *q)
{
	char			*ret;
	int				flag;
	int				i;
	unsigned int	n;
	unsigned int	t;

	flag = (num < 0);
	t = 1;
	i = 1 + (flag || (q->flags && q->flags->plus_space));
	if (flag && q->flags && q->flags->precision_set)
		q->flags->precision += 1;
	n = num;
	if (num < 0)
		n = 0 - num;
	while (n / t >= 10 && ++i)
		t *= 10;
	ret = handle_flag(i * sizeof(char), q, &i);
	if (int_help(ret, flag, q, &i) || prec_help(ret, q, n, i))
		return (ret);
	while (t)
	{
		ret[i++] = (((n / t) % 10) + '0');
		t /= 10;
	}
	return (ret);
}

char	*ptr_op(uintptr_t src, char type, t_queue *q, char *hex)
{
	int		i;
	int		k;
	int		min;
	char	*ret;
	char	*s;

	if (type == 'p' && src)
		return (uint_op((unsigned long) src, type, q, hex));
	s = (char *) src;
	i = 0;
	while (s && s[i])
		i ++;
	min = str_min(&s, i, q);
	ret = handle_flag(min * sizeof(char), q, &i);
	if (!ret)
		return (NULL);
	k = -1;
	while (++k < min)
		ret[i + k] = s[k];
	return (ret);
}
