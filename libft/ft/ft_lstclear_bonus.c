/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:53:27 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/21 03:52:43 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdelone_help(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*f;
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	f = *lst;
	while (f)
	{
		tmp = f->next;
		ft_lstdelone_help(f, del);
		f = tmp;
	}
	*lst = NULL;
}
