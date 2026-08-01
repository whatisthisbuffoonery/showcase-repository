/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:33 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:33 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//guaranteed non null
char	**count_str(t_arg *globbed)
{
	int		i;
	char	**ret;
	t_arg	*next;

	i = 0;
	next = globbed;
	while (next)
	{
		i ++;
		next = next->next;
	}
	ret = malloc((i + 1) * sizeof(char *));
	if (ft_err(-!ret, "malloc error"))
		return (NULL);
	i = 0;
	while (globbed)
	{
		next = globbed->next;
		ret[i++] = globbed->str;
		free(globbed->mask);
		free(globbed);
		globbed = next;
	}
	ret[i] = NULL;
	return (ret);
}

//src destroyed on failure
t_arg	*expand_globs(t_arg *fields)
{
	t_arg	*iter;
	t_arg	*next;
	t_arg	*prev;
	t_arg	*head;

	head = fields;
	iter = fields;
	prev = NULL;
	while (iter)
	{
		next = iter->next;
		if (!iter->assignment && has_glob(iter))
		{
			if (do_glob(&prev, &iter, &next, &head))
				return (free_arg_list(head));
		}
		else
			prev = iter;
		iter = next;
	}
	return (head);
}

char	**expand_all(t_tok *src, t_env *env, int (*f)(t_arg **, t_tok *))
{
	t_arg	*globbed;
	char	**ret;

	if (!src || expand_str(src, env) || f(&globbed, src))
		return (NULL);
	ret = count_str(globbed);
	if (!ret)
		free_arg_list(globbed);
	return (ret);
}
