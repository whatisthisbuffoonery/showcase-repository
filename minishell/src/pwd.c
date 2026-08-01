/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:47 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/21 13:10:14 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	pwd(t_env *env, int out)
{
	if (!env->pwd)
		env->pwd = getcwd(NULL, 0);
	if (env->pwd)
	{
		pwd_trim(env->pwd);
		ft_putstr_fd(env->pwd, out);
		ft_putchar_fd('\n', out);
	}
	return (builtin_err(!env->pwd, "pwd", "unable to recover pwd"));
}
