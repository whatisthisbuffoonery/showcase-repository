/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 18:32:00 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/17 18:32:01 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	heredoc_cmp(char *line, char *v, int v_len)
{
	int	line_len;

	if (!line)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd("heredoc delimited by EOF ", 2);
		ft_putstr_fd("(wanted: \'", 2);
		ft_putstr_fd(v, 2);
		ft_putstr_fd("\')\n", 2);
		return (0);
	}
	if (g_signo)
		return (0);
	line_len = ft_strlen(line);
	if (line_len != v_len)
		return (1);
	return (ft_strncmp(line, v, v_len));
}

//do_heredoc can end up with the wrong string ptr to free, so handle it here
int	heredoc_help(char *s, int fd)
{
	int	i;

	free(s);
	i = write(fd, "\n", 1);
	while (i < 0 && errno == EINTR && !g_signo)
		i = write(fd, "\n", 1);
	return (ft_err(i, "write error") < 0 || g_signo != 0);
}

int	heredoc_write(int *fd, char *s, t_env *env, int flag)
{
	int		i;
	int		k;
	int		len;
	t_tok	tmp;

	if (flag && !g_signo)
	{
		tmp.str = s;
		if (use_expansion(&tmp, env, NULL))
		{
			unset(&fd[0]);
			return (1);
		}
		s = tmp.str;
	}
	len = ft_strlen(s);
	i = 0;
	while (i < len && !g_signo)
	{
		k = write(fd[1], s, len - i);
		if (ft_err(-(k < 0 && errno != EINTR), "write error"))
			return (1);
		i += k + (k < 0);
	}
	return (heredoc_help(s, fd[1]));
}

int	do_heredoc(char *file, t_env *env, int flag)
{
	int		fd[2];
	char	*buf;
	int		v_len;

	if (ft_err(pipe(fd), "pipe error"))
		return (-1);
	errno = 0;
	buf = NULL;
	v_len = ft_strlen(file);
	rl_signal_event_hook = rl_heredoc;
	while (!g_signo)
	{
		buf = readline("> ");
		if (!heredoc_cmp(buf, file, v_len) || heredoc_write(fd, buf, env, flag))
			break ;
		buf = NULL;
	}
	free(buf);
	close(fd[1]);
	if (g_signo)
		unset(&fd[0]);
	rl_signal_event_hook = rl_handle_signals;
	return (fd[0]);
}

//allow empty string
char	**catch_heredoc(t_node *src, t_env *env, int (*f)(t_arg **, t_tok *))
{
	char	**file;

	if (ft_strcmp(src->redir_op->str, "<<"))
		return (expand_all(src->redir_target, env, f));
	file = NULL;
	if (!malloc_cond((void **) &file, 2 * sizeof(char *))
		|| !word_to_str(file, src->redir_target))
	{
		free(file);
		return (NULL);
	}
	file[1] = NULL;
	return (file);
}
