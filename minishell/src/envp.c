/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:25 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

char	**count_envp(t_env *env, int *complain)
{
	char		**ret;
	t_shnode	*iter;
	int			i;

	i = 0;
	iter = env->env;
	if (!iter)
		return (NULL);
	while (iter)
	{
		if (iter->name && iter->str)
			i ++;
		iter = iter->next;
	}
	ret = NULL;
	if (i)
	{
		ret = ft_calloc(i + 1, sizeof(char *));
		*complain = !ret;
	}
	return (ret);
}

char	**make_envp(t_env *env, int *complain)
{
	char		**ret;
	int			k;
	t_shnode	*iter;

	ret = count_envp(env, complain);
	if (ft_err(-(*complain != 0), "envp malloc error"))
		return (split_cleanup(ret));
	iter = env->env;
	k = 0;
	while (iter)
	{
		ret[k] = malloc(ft_strlen(iter->name) + ft_strlen(iter->str) + 1 + 1);
		if (ft_err(-!ret[k], "envp malloc error"))
		{
			*complain = 1;
			return (split_cleanup(ret));
		}
		ft_strlcpy(ret[k], iter->name, -1);
		ft_strlcat(ret[k], "=", -1);
		ft_strlcat(ret[k], iter->str, -1);
		iter = iter->next;
		k ++;
	}
	return (ret);
}
