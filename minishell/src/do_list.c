/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:29 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:29 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	do_list_subshell(t_node *node, t_env *env, int *fd)
{
	int	status;
	int	flag[2];

	status = 1;
	flag[0] = ft_err(dup2(fd[0], 0), "dup error subshell");
	flag[1] = ft_err(dup2(fd[1], 1), "dup error subshell");
	if (fd[0] > 2 && flag[0] >= 0)
		env->duped_fd[0] = 1;
	if (fd[1] > 2 && flag[1] >= 0)
		env->duped_fd[1] = 1;
	unset(&fd[0]);
	unset(&fd[1]);
	env->is_in_subshell = 1;
	if (flag[0] >= 0 && flag[1] >= 0)
		status = do_list(node, env);
	shell_cleanup(env);
	return (status);
}

int	do_group(t_node *node, t_env *env, int *pfd)
{
	int		fd[2];
	pid_t	pid;

	if (g_signo)
		return (g_signo);
	else if (redir_to_fd(node, env, fd, pfd))
		return (g_signo + !g_signo);
	else if (node->kind != N_GROUP)
		return (do_simple(node, env, fd));
	else if (env->do_not_subshell)
	{
		env->do_not_subshell = 0;
		return (do_list_subshell(node->left, env, fd));
	}
	else
	{
		pid = shell_fork(env);
		if (!pid)
			exit(do_list_subshell(node->left, env, fd));
		unset(&fd[0]);
		unset(&fd[1]);
		return (child_wait(pid));
	}
}

void	do_pipe_command(t_node *node, t_env *env, t_pipemanager *p, int p_index)
{
	int			status;
	int			fd[2];
	pid_t		pid;

	pid = shell_fork(env);
	pid_bump(p, pid);
	if (pid)
		return ;
	env->do_not_subshell = 1;
	fd[0] = p->pipes[p_index][0];
	p->pipes[p_index][0] = -1;
	if (fd[0] < 0)
		fd[0] = 0;
	fd[1] = 1;
	if (p_index)
	{
		fd[1] = p->pipes[p_index - 1][1];
		p->pipes[p_index - 1][1] = -1;
	}
	clean_pipemanager(p);
	status = do_group(node, env, fd);
	shell_cleanup(env);
	exit(status);
}

//i.e. a | b | c : c index 0, b index 1, a index 2 : p malloc 2 + 1 = 3 :
//a index 2 stdin = p[2][0] = 0, a index 2 - 1 stdout = p[1][1]
//b index 1 stdin = p[1][0], stdout = p[0][1]
//c index 0 stdin = p[0][0], !index: stdout = default to 1/outfile
int	do_pipe(t_node *node, t_env *env, t_pipemanager *p, int p_index)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 1;
	if (node->kind != N_PIPE || g_signo)
		return (do_group(node, env, fd));
	else if (node->left->kind == N_PIPE)
		do_pipe(node->left, env, p, p_index + 1);
	else
	{
		pipemanager_init(p, p_index + 1);
		if (p->pipes)
			do_pipe_command(node->left, env, p, p_index + 1);
	}
	if (!p->pipes)
		return (1);
	do_pipe_command(node->right, env, p, p_index);
	if (!p_index)
	{
		clean_pipemanager(p);
		return (child_wait(p->pid));
	}
	return (0);
}

int	do_list(t_node *node, t_env *env)
{
	int				status;
	t_pipemanager	p;

	p.pipes = NULL;
	p.pipe_count = 0;
	p.pid_count = 0;
	p.pid = 0;
	if (node->kind != N_AND && node->kind != N_OR)
		return (do_pipe(node, env, &p, 0));
	status = do_list(node->left, env);
	if (g_signo == SIGINT + 128 || (env->is_in_subshell && g_signo))
		return (g_signo);
	g_signo = 0;
	update_last(env, status);
	if (!g_signo && ((node->kind == N_AND && !status)
			|| (node->kind == N_OR && status)))
		status = do_list(node->right, env);
	return (status);
}
