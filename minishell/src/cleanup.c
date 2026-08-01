/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:12 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:12 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

void	tok_delone(t_tok *tok)
{
	free(tok->str);
	free(tok);
}

void	clean_tok(t_tok **tok)
{
	t_tok	*iter;
	t_tok	*next;

	iter = *tok;
	while (iter)
	{
		next = iter->next;
		clean_tok(&iter->word_next);
		tok_delone(iter);
		iter = next;
	}
	*tok = NULL;
}

void	clean_ast(t_node *node)
{
	if (!node)
		return ;
	clean_tok(&node->argv);
	clean_tok(&node->redir_op);
	clean_tok(&node->redir_target);
	clean_ast(node->redir_next);
	clean_ast(node->left);
	clean_ast(node->right);
	free(node);
}
