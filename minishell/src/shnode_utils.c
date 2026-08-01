/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shnode_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:53 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:53 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	shnode_strlen(t_shnode *env)
{
	if (env && env->str)
		return (ft_strlen(env->str));
	return (0);
}

t_shnode	*shnode_dup(t_shnode *src)
{
	t_shnode	*ret;

	if (!src)
		return (NULL);
	ret = malloc(sizeof(t_shnode));
	if (ft_err(-!ret, "shnode dup malloc"))
		return (NULL);
	ret->name = src->name;
	ret->str = src->str;
	ret->next = NULL;
	return (ret);
}

void	shnode_append(t_shnode **dst, t_shnode *src)
{
	t_shnode	*iter;

	iter = *dst;
	while (iter && iter->next)
		iter = iter->next;
	if (iter)
		iter->next = src;
	else
		*dst = src;
}

int	env_add(t_env *env, t_shnode *src, char *dst)
{
	t_shnode	*ret;
	t_shnode	**list;

	ret = src;
	list = &env->export;
	if (dst[1] == 'n')
	{
		ret = shnode_dup(src);
		list = &env->env;
	}
	if (ret)
		ret->next = NULL;
	shnode_append(list, ret);
	return (0);
}
