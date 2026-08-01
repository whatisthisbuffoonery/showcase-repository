/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:31 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:31 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	exit_arg(char *v, int *flag)
{
	int	i;

	i = 0;
	while (ft_isspace(v[i]))
		i ++;
	if (v[i] == '+' || v[i] == '-')
		i ++;
	*flag += !v[i];
	while (ft_isdigit(v[i]))
		i ++;
	while (ft_isspace(v[i]))
		i ++;
	*flag += (v[i] != 0);
	if (*flag)
		return (shell_assert2(1 + 1, v, "numeric argument required"));
	return (ft_atoi(v) % 256);
}

//always prints to stderr//also yes it prints before checking for too many args
//does not exit on too many args
int	exit_builtin(int argc, char **argv, t_env *env, int *fd)
{
	int	status;
	int	flag;

	flag = 0;
	ft_putstr_fd("exit\n", 2);
	if (shell_assert2(argc > 2, "exit", "too many arguments"))
		return (1);
	else if (argc > 1)
		status = exit_arg(argv[1], &flag);
	else
		status = env->last;
	shell_cleanup(env);
	split_cleanup(argv);
	unset(&fd[0]);
	unset(&fd[1]);
	exit(status);
	return (0);
}
