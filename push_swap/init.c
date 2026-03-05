/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:22:19 by dthoo             #+#    #+#             */
/*   Updated: 2026/01/17 12:22:24 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_ps.h"

/*
tests:
-12-34 > alien check
-- > front flag check
"- " > back flag check
*/

static int	int_count(char *v)
{
	int		i;
	int		flag;
	int		local_count;

	i = 0;
	flag = 0;
	local_count = 0;
	while (v[i])
	{
		if (v[i] == '-' && !flag++ && ++i)
			continue ;
		else if (v[i] == '-' && flag)
			return (0);
		if (v[i] >= '0' && v[i] <= '9' && ++local_count)
			flag = 0;
		while (v[i] >= '0' && v[i] <= '9')
			i ++;
		if (flag || (v[i] && v[i] != ' '))
			return (0);
		i += (v[i] != '\0');
	}
	return (local_count);
}

static int	iter_atoi(int *index, char *v, int *out, int *iter)
{
	int				i;
	int				flag;
	unsigned int	a;
	unsigned int	tmp;

	i = *index;
	a = 0;
	flag = 1;
	while (v[i] == ' ')
		i ++;
	if (v[i] == '-' && ++i)
		flag = -1;
	while (v[i] >= '0' && v[i] <= '9')
	{
		tmp = (a * 10) + (v[i++] - '0');
		if (tmp < a || tmp > (((unsigned int)(INT_MAX)) + (flag == -1)))
			return (1);
		a = tmp;
	}
	while (v[i] == ' ')
		i ++;
	*index = i * (v[i] != '\0');
	*iter += (v[i] == '\0');
	*out = a * flag;
	return (0);
}

static int	*make_array(int *ret, char **v, int max)
{
	int	i;
	int	cmp;
	int	ptr_index;
	int	ret_index;
	int	str_index;

	ptr_index = 0;
	ret_index = max;
	str_index = 0;
	while (v[ptr_index])
	{
		if (iter_atoi(&str_index, v[ptr_index], &ret[ret_index], &ptr_index))
			return ((free(ret)), NULL);
		i = max;
		cmp = ret[ret_index];
		while (i > ret_index)
		{
			if (ret[i--] == cmp)
				return ((free(ret)), NULL);
		}
		ret_index --;
	}
	return (ret);
}

static int	*validate(int *c, char **v)
{
	int		tmp;
	int		*ret;
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < *c)
	{
		tmp = int_count(v[i]);
		if (!tmp)
			return (NULL);
		count += tmp;
	}
	ret = malloc((count) * sizeof(int));
	if (!ret)
		return (NULL);
	*c = count;
	return (make_array(ret, v, count - 1));
}

int	init(int c, char **v, t_stack **a, t_stack **b)
{
	int	*arr;

	arr = validate(&c, v);
	if (!arr)
		return (1);
	*a = malloc(sizeof(t_stack));
	*b = malloc(sizeof(t_stack));
	if (!*a || !*b)
		return ((free(arr)), 1);
	(*a)->arr = arr;
	(*b)->arr = malloc(c * sizeof(int));
	if (!(*b)->arr)
		return (1);
	(*a)->top = c - 1;
	(*b)->top = -1;
	return (0);
}
