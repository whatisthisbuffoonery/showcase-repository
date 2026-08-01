/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:30:43 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:30:48 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	isempty(char *buf)
{
	int	i;

	if (!buf)
		return (1);
	i = 0;
	while (buf[i] && ft_isspace(buf[i]))
		i ++;
	return (!buf[i]);
}

int	quote_check(char *buf)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (buf[i])
	{
		if (!c && ft_isquote(buf[i]))
			c = buf[i];
		else if (c && buf[i] == c)
			c = 0;
		i ++;
	}
	return (shell_assert(c, "unclosed quotes"));
}

int	buf_check(char *buf, t_env *env)
{
	if(isempty(buf))
		return (1);
	else if (quote_check(buf))
	{
		update_last(env, 2);
		return (1);
	}
	return (0);
}
