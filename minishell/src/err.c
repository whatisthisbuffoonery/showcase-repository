/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:27 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:27 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//check for [] printing
int	shell_assert_redir(int cond, t_tok *src, char *s)
{
	if (cond)
	{
		ft_putstr_fd("-minishell: ", 2);
		print_word(src);
		if (src)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s, 2);
		ft_putchar_fd('\n', 2);
	}
	return (cond);
}

int	shell_assert2(int cond, char *name, char *s)
{
	if (cond)
	{
		ft_putstr_fd("-minishell: ", 2);
		if (!name)
			name = "(null)";
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(s, 2);
		ft_putchar_fd('\n', 2);
	}
	return (cond);
}

int	builtin_err(int cond, char *name, char *s)
{
	if (cond)
	{
		ft_putstr_fd("-minishell: ", 2);
		if (!name)
			name = "(null)";
		if (!s)
			s = "(null)";
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		perror(s);
	}
	return (cond);
}

int	shell_assert(int cond, char *s)
{
	if (cond)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putchar_fd('\n', 2);
	}
	return (cond);
}

int	ft_err(int n, char *s)
{
	if (n < 0)
	{
		ft_putstr_fd("-minishell: ", 2);
		perror(s);
	}
	return (n);
}
