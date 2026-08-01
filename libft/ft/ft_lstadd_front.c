/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:20:59 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/20 00:23:15 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*f;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		f = *lst;
		*lst = new;
		new->next = f;
	}
}
