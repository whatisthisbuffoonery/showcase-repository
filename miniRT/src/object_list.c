/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:26:53 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:26:55 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

t_object	*object_new(t_obj_type type)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	return (obj);
}

void	object_add_back(t_object **lst, t_object *new)
{
	t_object	*node;

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
