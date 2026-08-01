/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:50 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:51 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	set_fd(int *fd, int *pfd)
{
	if (fd[0] < 2)
		fd[0] = pfd[0];
	else
		unset(&pfd[0]);
	if (fd[1] < 2)
		fd[1] = pfd[1];
	else
		unset(&pfd[1]);
}

//if flag, close all fds
//else, set_fd
int	select_fd(int *fd, int *pfd, int flag)
{
	if (flag)
	{
		unset(&fd[0]);
		unset(&fd[1]);
		unset(&pfd[0]);
		unset(&pfd[1]);
	}
	else
		set_fd(fd, pfd);
	return (flag);
}

//no need to iterate here 
int	update_redir_fd(int *fd, char **file, t_node *iter, t_env *env)
{
	int		id;
	int		new_fd;
	char	*op;

	op = iter->redir_op->str;
	id = (op[0] == '>');
	if (!id && op[1])
		new_fd = do_heredoc(*file, env, iter->heredoc);
	else if (!id)
		new_fd = open(*file, O_RDONLY);
	else if (id && op[1])
		new_fd = open(*file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		new_fd = open(*file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	unset(&fd[id]);
	fd[id] = new_fd;
	return (g_signo != 0 || ft_err(new_fd, "open error") < 0);
}

static int	super_big_cond(char **file, t_tok *src)
{
	int	cond[2];

	if (!file)
		return (1);
	cond[0] = (!file[0] || file[1]);
	cond[1] = (!file[0][0] && !ft_strcmp(src->str, "<<"));
	return (shell_assert_redir(cond[0] || cond[1], src, "ambiguous redirect"));
}

int	redir_to_fd(t_node *node, t_env *env, int *fd, int *pfd)
{
	char	**file;
	t_node	*iter;
	int		flag;

	fd[0] = 0;
	fd[1] = 1;
	iter = node->redir_next;
	flag = 0;
	while (iter && !flag)
	{
		iter->heredoc = !find_quote(iter->redir_target);
		file = catch_heredoc(iter, env, collect_redir);
		if (super_big_cond(file, iter->redir_target))
		{
			split_cleanup(file);
			return (1);
		}
		flag = update_redir_fd(fd, file, iter, env);
		split_cleanup(file);
		iter = iter->redir_next;
	}
	return (select_fd(fd, pfd, flag));
}
