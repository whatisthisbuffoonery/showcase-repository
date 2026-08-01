/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:11 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:11 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	isenv(char c)
{
	return (c == '_' || ft_isalnum(c));
}

int	isbuiltin(char *s)
{
	return (!ft_strcmp(s, "env") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "echo") || !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset") || !ft_strcmp(s, "exit"));
}

int	envname(char *s)
{
	return (s[0] == '$' && (s[1] == '_' || ft_isalpha(s[1]) || s[1] == '?'));
}

//only when export is argv[0] of the cmd
int	is_assignment_word(char *s)
{
	int	i;

	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (s[i] == '=');
}

int	find_quote(t_tok *tok)
{
	while (tok)
	{
		if (ft_isquote(tok->type))
			return (1);
		tok = tok->word_next;
	}
	return (0);
}
