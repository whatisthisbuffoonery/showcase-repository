/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:24:14 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:24:16 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

char	*require_token(char **tokens, int i, t_rt *rt)
{
	if (!tokens[i])
		msg_exit("unexpected end of file: missing element field", rt);
	return (tokens[i]);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}
