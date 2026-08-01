/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 15:36:31 by achew             #+#    #+#             */
/*   Updated: 2026/05/08 17:37:54 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

t_shnode	*extract_env(t_shnode **head, char *v)
{
	t_shnode	*prev;
	t_shnode	*iter;

	iter = *head;
	prev = NULL;
	while (iter && ft_strcmp(iter->name, v))
	{
		prev = iter;
		iter = iter->next;
	}
	if (!iter)
		return (NULL);
	else if (!prev)
		*head = iter->next;
	else
		prev->next = iter->next;
	iter->next = NULL;
	return (iter);
}

int	unset_builtin(int argc, char **argv, t_env *env)
{
	t_shnode	*tmp;
	int			i;

	if (argc < 2)
		return (0);
	i = 1;
	while (argv[i])
	{
		tmp = extract_env(&env->env, argv[i]);
		clean_shnode_dup(&tmp);
		tmp = extract_env(&env->export, argv[i]);
		clean_shnode(&tmp);
		i++;
	}
	return (0);
}
