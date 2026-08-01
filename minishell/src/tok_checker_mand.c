/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_checker_mand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:31:42 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:31:44 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	isredir(int c)
{
	return (c == '>' || c == '<');
}

int	isbracket(int c)
{
	(void) c;
	return (0);
}

int	iscond(int c)
{
	return (c == '|');
}

int	isop(int c)
{
	return (isredir(c) || iscond(c));
}

/*&& c != '='  do not consider */
int	iscontent(int c)
{
	return (c
		&& !isop(c) && !ft_isquote(c) && !ft_isspace(c) && !isbracket(c));
}
