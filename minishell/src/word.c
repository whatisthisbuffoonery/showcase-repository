/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:49:12 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:49:12 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

char	*word_to_str(char **dst, t_tok *src)
{
	int		i;
	char	*ret;
	t_tok	*iter;

	i = 0;
	iter = src;
	while (iter)
	{
		i += ft_strlen(iter->str);
		iter = iter->word_next;
	}
	if (!malloc_cond((void **) &ret, i + 1))
		return (NULL);
	ret[0] = '\0';
	iter = src;
	while (iter)
	{
		ft_strlcat(ret, iter->str, i + 1);
		iter = iter->word_next;
	}
	if (dst)
		*dst = ret;
	return (ret);
}

void	make_word(t_tok *iter)
{
	t_tok	*next;

	while (iter)
	{
		if (isjoined(iter))
		{
			iter->word_next = subtok(&iter->next, isjoined);
			next = iter->word_next;
			while (next)
			{
				next->word_next = next->next;
				next->next = NULL;
				next = next->word_next;
			}
		}
		iter = iter->next;
	}
}

void	print_word(t_tok *tok)
{
	if (!tok)
		return ;
	ft_putstr("[");
	ft_putstr(tok->str);
	while (tok->word_next)
	{
		tok = tok->word_next;
		ft_putstr(tok->str);
	}
	ft_putstr("]");
}
