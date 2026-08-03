/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:31 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/11 17:28:32 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		type_bus(t_pf_q *q, const char *format, char *type);
t_pf_q	*q_new(void);

static void	*tantrum(t_pf_q **a, char **b)
{
	if (*a)
	{
		if ((*a)->flags)
			free((*a)->flags);
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	return (NULL);
}

t_pf_q	*new_op(const char *format, int *index, char *type)
{
	t_pf_q	*ret;

	ret = q_new();
	*index += 2 + type_bus(ret, &format[1], type);
	if (!ret || !ret->arg)
		return (tantrum(&ret, NULL));
	ret->type = op;
	return (ret);
}

t_pf_q	*new_str(const char *format, int start, int *end)
{
	int		i;
	int		flag;
	t_pf_q	*ret;
	char	*res;

	ret = q_new();
	flag = (format[*end] && format[*end + 1] == '%');
	*end += flag;
	res = malloc(((*end - start) + 1) * sizeof(char));
	i = -1;
	if (!ret || !res)
		return (tantrum(&ret, &res));
	while (start + ++i < *end)
		res[i] = format[i + start];
	res[i] = '\0';
	ret->str = res;
	*end += flag;
	ret->type = str;
	return (ret);
}
