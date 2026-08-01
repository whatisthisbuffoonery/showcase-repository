/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_mand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:02:50 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/18 22:02:52 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//this splits words, quotes, and operators &, |, >, <

//splitting words from quotes is done for simplicity,
//but should be recombined if they were not separated by whitespace

//check for ending whitespace, ls'>'wa should stay as one element
int	tok_node_init(t_tok **dst, char *src, int *cry)
{
	int		i;
	char	c;
	t_tok	*ret;

	i = 0 + 1;
	c = src[0];
	while (!g_signo && ((isredir(c) && src[i] == c && i < 2)
			|| (iscontent(c) && iscontent(src[i]))
			|| (ft_isquote(c) && src[i] && src[i] != c)
			|| (iscond(c) && i < 1)))
		i ++;
	ret = tok_node(src, i, c, cry);
	tok_node_append(dst, ret);
	return (i + hadquote(src, i));
}

int	simple_cond(t_tok *src)
{
	if (!src || !src->type || iscond(src->type))
		return (0);
	return (1);
}

t_node_kind	find_kind_op(t_tok *tok)
{
	(void) tok;
	return (N_CMD);
}

int	group_kind(char c)
{
	(void) c;
	return (0);
}
