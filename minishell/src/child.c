/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:11 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:11 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//removed shlvl update
void	env_import(t_env *env)
{
	t_shnode	*iter;
	t_shnode	*prev;
	t_shnode	*next;

	prev = NULL;
	iter = env->export;
	while (iter)
	{
		next = iter->next;
		if (!iter->str)
		{
			if (prev)
				prev->next = iter->next;
			else
				env->export = iter->next;
			clean_one_shnode(iter);
		}
		else
			prev = iter;
		iter = next;
	}
}

pid_t	shell_fork(t_env *env)
{
	pid_t	pid;

	(void)env;
	if (g_signo)
		return (-1);
	pid = fork();
	return (ft_err(pid, "shell fork"));
}

void	pid_bump(t_pipemanager *p, pid_t src)
{
	p->pid = src;
	p->pid_count += 1;
}

//check for negative pid and set status to 1
int	child_wait(pid_t pid)
{
	int	status;
	int	n;

	errno = 0;
	status = 1;
	while (pid > 0 && waitpid(pid, &n, 0) < 0 && errno == EINTR)
		errno = 0;
	if (pid < 1)
		status = g_signo + !g_signo;
	else if (errno != ECHILD)
	{
		status = WEXITSTATUS(n);
		if (WIFSIGNALED(n))
			status = WTERMSIG(n) + 128;
		errno = 0;
	}
	while (1)
	{
		if (wait(NULL) < 0 && errno != EINTR)
			break ;
		errno = 0;
	}
	return (status);
}
