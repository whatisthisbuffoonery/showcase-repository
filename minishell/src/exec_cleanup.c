/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:30 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:30 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	clean_pipemanager(t_pipemanager *p)
{
	pipeset_cleanup(p->pipes, p->pipe_count);
}

void	shell_cleanup(t_env *env)
{
	clean_ast(env->ast);
	env->ast = NULL;
	clean_shnode(&env->export);
	clean_shnode_dup(&env->env);
	if (env->duped_fd[0])
		close(0);
	if (env->duped_fd[1])
		close(1);
	env->duped_fd[0] = 0;
	env->duped_fd[1] = 0;
	free(env->pwd);
	free(env->oldpwd);
	env->pwd = NULL;
	env->oldpwd = NULL;
	rl_clear_history();
}

char	*absent_command_str(char *v)
{
	if (ft_strchr(v, '/'))
		return ("No such file or directory");
	return ("command not found");
}
