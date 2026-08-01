/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_empty_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 17:26:24 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/21 17:26:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	move_argv(char **argv)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *argv;
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i ++;
	}
	free(tmp);
}

int	argv_check_quote(t_tok *src)
{
	while (src)
	{
		if (ft_isquote(src->type))
			return (1);
		src = src->word_next;
	}
	return (0);
}

int	argv_any_empty(char **v, int *index)
{
	int	i;

	i = *index;
	while (v[i])
	{
		if (!v[i][0])
		{
			*index = i;
			return (1);
		}
		i ++;
	}
	return (0);
}

int	isglob(t_tok *src)
{
	if (ft_isquote(src->type))
		return (0);
	return (ft_strchr(src->str, '*') != NULL);
}

void	align_argv(char **v, int *i, t_tok **s)
{
	t_tok	*src;

	if (!isglob(*s))
		return ;
	*s = (*s)->next;
	src = *s;
	if (!src)
		return ;
	else if (!argv_any_empty(v, i))
	{
		*s = NULL;
		return ;
	}
	while (src && src->str[0])
		src = src->next;
	*s = src;
}
