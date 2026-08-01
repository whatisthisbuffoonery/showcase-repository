/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:31:08 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:31:09 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

static t_shnode	*find_env_internal(char *str, t_shnode *list, unsigned int n)
{
	while (list && (ft_strlen(list->name) != n
			|| ft_strncmp(str, list->name, n)))
		list = list->next;
	return (list);
}

t_shnode	*find_env(char *str, t_shnode *list)
{
	size_t	matchlen;

	matchlen = ft_strlen(str);
	while (list && (ft_strlen(list->name) != matchlen
			|| ft_strncmp(str, list->name, matchlen)))
		list = list->next;
	return (list);
}

//turn status assignment into a func ig
char	*find_env_str(char *name, t_env *env, unsigned int len)
{
	t_shnode	*ret;

	if (!name || !name[0])
		return (NULL);
	else if (name[0] == '?')
		return (env->last_string);
	else if (len)
	{
		ret = find_env_internal(name, env->env, len);
		if (ret)
			return (ret->str);
	}
	return (NULL);
}
