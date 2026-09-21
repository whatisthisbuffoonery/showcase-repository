/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:26:09 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:26:11 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

t_light	*light_new(void)
{
	return (ft_calloc(1, sizeof(t_light)));
}

void	light_add_back(t_light **lst, t_light *new)
{
	t_light	*node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
}
