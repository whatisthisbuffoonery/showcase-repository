/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:02:20 by achew             #+#    #+#             */
/*   Updated: 2026/04/28 18:17:07 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	print_env(t_shnode *env, int fd)
{
	while (env)
	{
		ft_putstr_fd(env->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(env->str, fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
}

int	env_builtin(int argc, char **argv, t_env *env, int fd)
{
	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("only support env without options and arguments\n", 2);
		return (125);
	}
	print_env(env->env, fd);
	return (0);
}
