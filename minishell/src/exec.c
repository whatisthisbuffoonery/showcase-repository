/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:31:00 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:31:01 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	update_last(t_env *env, unsigned int n)
{
	int	i;
	int	t;

	n %= 256;
	i = 0;
	t = 1;
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		env->last_string[i++] = ((n / t) % 10) + '0';
		t /= 10;
	}
	env->last_string[i] = '\0';
	env->last = n;
}

int	do_builtin_match(int argc, char **argv, t_env *env, int *fd)
{
	int	status;

	status = 0;
	errno = 0;
	if ((*argv)[0] == 'c')
		status = cd(argc, argv, env);
	else if ((*argv)[0] == 'u')
		status = unset_builtin(argc, argv, env);
	else if ((*argv)[0] == 'p')
		status = pwd(env, fd[1]);
	else if ((*argv)[1] == 'n')
		status = env_builtin(argc, argv, env, fd[1]);
	else if ((*argv)[1] == 'c')
		status = echo(argv, fd[1]);
	else if ((*argv)[2] == 'p')
		status = ft_export(argc, argv, env, fd[1]);
	else if ((*argv)[2] == 'i')
		status = exit_builtin(argc, argv, env, fd);
	status += builtin_err(!status && errno, *argv, "write error");
	return (status);
}

int	do_binary(char **argv, t_env *env, int *fd)
{
	char		**envp;
	int			status;

	status = g_signo;
	envp = NULL;
	errno = 0;
	if (!status)
		envp = make_envp(env, &status);
	if (!status)
		status = ft_err(-(dup2(fd[0], 0) < 0
					|| dup2(fd[1], 1) < 0), "dup error");
	unset(&fd[0]);
	unset(&fd[1]);
	if (!status)
		ft_err(execve(*argv, argv, envp), *argv);
	status = 126 + (access(*argv, F_OK) != 0);
	close(0);
	close(1);
	shell_cleanup(env);
	split_cleanup(argv);
	split_cleanup(envp);
	return (status);
}

int	exec_simple(int argc, char **argv, t_env *env, int *fd)
{
	pid_t	pid;

	if (isbuiltin(*argv))
		return (do_builtin_match(argc, argv, env, fd));
	pid = 0;
	if (!env->do_not_subshell)
		pid = shell_fork(env);
	if (pid < 0)
		return (1);
	env->do_not_subshell = 0;
	if (!pid)
		exit(do_binary(argv, env, fd));
	else
		return (child_wait(pid));
}

int	do_simple(t_node *node, t_env *env, int *fd)
{
	char	**argv;
	int		status;
	int		i;

	argv = NULL;
	status = 0;
	if (!node->argv)
	{
		unset(&fd[0]);
		unset(&fd[1]);
		return (0);
	}
	argv = make_argv(node->argv, env, &status);
	status += !argv;
	i = 0;
	while (argv && argv[i])
		i ++;
	if (argv && argv[0] && !status)
		status = exec_simple(i, argv, env, fd);
	else if (argv && status == ENOENT)
		status = shell_assert2(127, *argv, absent_command_str(*argv));
	split_cleanup(argv);
	unset(&fd[0]);
	unset(&fd[1]);
	return (status);
}
