/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:06 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:06 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

//further separation efforts here
t_node	*parse_simple(t_tok **tok, int *stop)
{
	t_node	*new_cmd;

	if (!simple_cond(*tok))
	{
		ft_putstr_fd("expected command, got ", 2);
		if (!*tok)
			ft_putstr_fd("EOF", 2);
		else
			ft_putstr_fd((*tok)->str, 2);
		ft_putstr_fd("\n", 2);
		*stop = 1;
		return (NULL);
	}
	new_cmd = node_new(N_CMD, stop);
	if (!new_cmd)
		return (NULL);
	while (!*stop && simple_cond(*tok))
	{
		if (isredir((*tok)->type))
			redir_append(new_cmd, parse_one_redir(tok, stop));
		else
			tok_node_append(&new_cmd->argv, subtok(tok, single_tok));
	}
	return (new_cmd);
}

t_node	*parse_group(t_tok **tok, int *stop)
{
	t_node	*new_group;

	tok_pop(tok);
	new_group = node_new(N_GROUP, stop);
	if (!new_group)
		return (NULL);
	new_group->left = parse_list(tok, stop);
	if (*stop)
		return (new_group);
	if (!*tok || (*tok)->type != ')')
	{
		ft_putstr_fd("syntax error: unclosed brackets\n", 2);
		*stop = 1;
		return (new_group);
	}
	tok_pop(tok);
	new_group->redir_next = parse_redir_group(tok, stop);
	return (new_group);
}

t_node	*parse_command(t_tok **tok, int *stop)
{
	if (!*tok)
	{
		ft_putstr_fd("syntax error: unexpected end of input\n", 2);
		*stop = 1;
		return (NULL);
	}
	if (group_kind((*tok)->type))
		return (parse_group(tok, stop));
	return (parse_simple(tok, stop));
}

t_node	*parse_pipeline(t_tok **tok, int *stop)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_pipe;

	left = parse_command(tok, stop);
	if (!left || *stop)
		return (left);
	while (*tok && !*stop && !ft_strcmp((*tok)->str, "|"))
	{
		new_pipe = node_new(N_PIPE, stop);
		if (!new_pipe)
			return (left);
		tok_pop(tok);
		right = parse_command(tok, stop);
		new_pipe->left = left;
		new_pipe->right = right;
		left = new_pipe;
	}
	return (left);
}

t_node	*parse_list(t_tok **tok, int *stop)
{
	t_node	*left;
	t_node	*right;
	t_node	*new_op;

	left = parse_pipeline(tok, stop);
	if (!left || *stop)
		return (left);
	while (*tok && !*stop && ast_iscond(*tok))
	{
		new_op = node_new(find_kind_op(*tok), stop);
		if (!new_op)
			return (left);
		tok_pop(tok);
		right = parse_pipeline(tok, stop);
		new_op->left = left;
		new_op->right = right;
		left = new_op;
	}
	return (left);
}
