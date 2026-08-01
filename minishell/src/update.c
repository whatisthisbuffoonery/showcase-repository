/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:49:11 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:49:11 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//bash hands off an updated shell lvl already for v5.2.x, campus coms use 5.1.16
int	update_shell_lvl(t_env *dst, int is_subshell)
{
	t_shnode	*iter;
	char		*ret;

	iter = find_env("SHLVL", dst->export);
	if (!iter)
	{
		iter = env_init_node("SHLVL=1");
		if (!iter)
			return (ft_err(-!is_subshell, "could not replace missing shlvl"));
		env_add(dst, iter, "env");
		env_add(dst, iter, "export");
		return (0);
	}
	if (iter->str)
		ret = ft_itoa(ft_atoi(iter->str) + 1);
	else
		ret = ft_itoa(1);
	if (!ret)
		return (ft_err(-!is_subshell, "shlvl update error"));
	free(iter->str);
	iter->str = ret;
	iter = find_env("SHLVL", dst->env);
	if (iter)
		iter->str = ret;
	return (shell_assert(!iter && !is_subshell, "shlvl missing in env"));
}
