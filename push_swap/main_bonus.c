/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:34 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 15:13:06 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

int	sorted(t_stack *a, t_stack *b)
{
	int	top;
	int	i;

	if (b && b->top != -1)
		return (0);
	top = a->top;
	i = 0;
	while (i < top)
	{
		if (a->arr[i] < a->arr[i + 1])
			return (0);
		i ++;
	}
	return (1);
}

static void	ps_clear(t_stack *a, t_stack *b)
{
	if (a)
		free(a->arr);
	if (b)
		free(b->arr);
	free(a);
	free(b);
}

void	ps_line(unsigned char *dst, int *flag, int i)
{
	static unsigned char	buf[1024];
	static int				curr;
	static int				lim;

	if (curr >= lim)
	{
		curr = 0;
		lim = read(0, buf, 1024);
	}
	if (lim < 1 || i > 3)
	{
		*flag = ((lim == 0) - (lim < 0)) - (2 * (i > 3));
		return ;
	}
	while (curr < lim && i < 4)
	{
		dst[i] = buf[curr];
		i ++;
		curr ++;
		if (dst[i - 1] == '\n')
			break ;
	}
	dst[i] = '\0';
	if (dst[i - 1] != '\n')
		ps_line(dst, flag, i);
}

void	ps_check(t_stack *a, t_stack *b)
{
	int				flag;
	unsigned char	in[5];
	unsigned char	table[3][256];

	flag = 0;
	table_init(table);
	ps_line(&in[0], &flag, 0);
	while (flag < 1)
	{
		if (flag < 0 || ps_alien(&in[0], table))
		{
			write(2, "Error\n", 6);
			return ;
		}
		else
			ps_exec(a, b, &in[0], flag);
		ps_line(&in[0], &flag, 0);
	}
	if (sorted(a, b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int c, char **v)
{
	t_stack			*a;
	t_stack			*b;

	a = NULL;
	b = NULL;
	if (c < 2)
		return (0);
	ps_write("checker");
	if (!init(c - 1, &v[1], &a, &b))
		ps_check(a, b);
	else
		write(2, "Error\n", 6);
	ps_clear(a, b);
}
