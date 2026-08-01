/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:42 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:42 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

t_arg	*arg_init(t_tok *iter)
{
	int		i;
	t_arg	*ret;

	i = 0;
	while (iter)
	{
		i += ft_strlen(iter->str);
		iter = iter->word_next;
	}
	ret = ft_calloc(1, sizeof(t_arg));
	if (ret)
	{
		ret->mask = ft_calloc(i + 1, sizeof(char));
		ret->str = ft_calloc(i + 1, sizeof(char));
		if (!ret->mask || !ret->str)
		{
			free(ret->mask);
			free(ret->str);
			free(ret);
			ret = NULL;
		}
		else
			ret->str[0] = '\0';
	}
	return (ret);
}

//check null token in parent
int	split_expand(t_arg **dst, t_tok *src)
{
	int		i;
	int		len;

	*dst = arg_init(src);
	if (*dst)
		(*dst)->assignment = src->assignment;
	len = 0;
	while (*dst && src)
	{
		i = 0;
		while (src->str && src->str[i])
		{
			if (!ft_isquote(src->type)
				&& (ft_isspace(src->str[i]) || src->str[i] == '*'))
				(*dst)->mask[len + i] = 1;
			else
				(*dst)->mask[len + i] = 0;
			i ++;
		}
		len += i;
		ft_strlcat((*dst)->str, src->str, -1);
		src = src->word_next;
	}
	return (ft_err(-!*dst, "expansion splitting malloc"));
}

t_arg	*new_field(t_arg *src, int start, int end)
{
	t_arg	*node;
	int		len;

	len = end - start;
	node = ft_calloc(1, sizeof(t_arg));
	if (!node)
		return (NULL);
	node->str = ft_calloc(len + 1, sizeof(char));
	node->mask = ft_calloc(len + 1, sizeof(char));
	if (!node->str || !node->mask)
	{
		free(node->str);
		free(node->mask);
		free(node);
		return (NULL);
	}
	ft_strlcpy(node->str, &src->str[start], len + 1);
	ft_memcpy(node->mask, &src->mask[start], len);
	return (node);
}

t_arg	*append_new_field(t_arg **head, t_arg **cur, t_arg *new)
{
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
		(*cur)->next = new;
	*cur = new;
	return (new);
}

//for empty word i.e. $c="     " unquoted, this returns src
//caller of this has to weed out completely empty entries
//(!head) condition checks if src->str was empty
t_arg	*field_split(t_arg *src)
{
	t_arg	*head;
	t_arg	*cur;
	int		start;	
	int		next_to_1;
	int		i;

	head = NULL;
	i = 0;
	next_to_1 = 0;
	start = 0;
	while (src->str[i])
	{
		if (src->mask[i] && ft_isspace(src->str[i]) && !next_to_1 && i > start
			&& !append_new_field(&head, &cur, new_field(src, start, i)))
			return (free_arg_list(head));
		next_to_1 = src->mask[i] && ft_isspace(src->str[i]);
		if (next_to_1)
			start = i + 1;
		i++;
	}
	if (i > start && !(append_new_field(&head, &cur, new_field(src, start, i))))
		return (free_arg_list(head));
	if (!head)
		return (src);
	return (head);
}
