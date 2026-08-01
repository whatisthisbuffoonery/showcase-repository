/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 07:48:02 by dthoo             #+#    #+#             */
/*   Updated: 2026/06/14 07:48:02 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minishell.h"

int	single_tok(t_tok *iter)
{
	(void) iter;
	return (0);
}

int	isname(t_tok *node)
{
	return (node && (iscontent(node->type) || ft_isquote(node->type)
			|| node->type == '*' || node->type == '='));
}

int	isjoined(t_tok *node)
{
	return (isname(node) && isname(node->next) && !node->end_space);
}

int	ismeta(t_tok *tok)
{
	return (tok && (iscond(tok->type) || isbracket(tok->type)));
}
