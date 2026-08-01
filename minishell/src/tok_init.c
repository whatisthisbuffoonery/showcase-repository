/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:55 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:55 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	hadquote(char *s, int n)
{
	return (ft_isquote(s[0]) != 0 && s[n] == s[0]);
}

t_tok	*tok_node(char *src, int i, char c, int *cry)
{
	t_tok	*ret;

	ret = ft_calloc(sizeof(t_tok), 1);
	if (!ret)
	{
		*cry = 1;
		ft_err(-1, "tok node malloc");
		return (NULL);
	}
	shell_assert(!i || !c, "zero string???? how???????\n");
	ret->str = ft_substr(src, hadquote(src, i), i - hadquote(src, i));
	if (!ret->str)
		*cry = (ft_err(-1, "tok node str malloc"));
	ret->type = c;
	if (ret->str && !ft_strcmp(ret->str, "&"))
		ret->type = "me is name node"[0];
	ret->end_space = ft_isspace(src[i + hadquote(src, i)]);
	return (ret);
}

void	tok_node_append(t_tok **dst, t_tok *src)
{
	t_tok	*iter;

	iter = *dst;
	while (iter && iter->next)
		iter = iter->next;
	if (!iter)
		*dst = src;
	else
		iter->next = src;
}

int	tok_init(char *buf, t_tok **tok)
{
	int	i;
	int	cry;

	i = 0;
	cry = 0;
	while (buf && buf[i] && !cry)
	{
		while (ft_isspace(buf[i]))
			i ++;
		if (!buf[i])
			break ;
		i += tok_node_init(tok, &buf[i], &cry);
		if (cry)
			return (1);
	}
	return (cry);
}
