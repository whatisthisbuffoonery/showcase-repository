/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 01:14:45 by dthoo             #+#    #+#             */
/*   Updated: 2025/11/23 17:03:57 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	var_help(t_list **head, t_list **curr, t_list *tmp)
{
	if (!*head)
	{
		*head = tmp;
		*curr = tmp;
		return ;
	}
	(*curr)->next = tmp;
	*curr = (*curr)->next;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;
	t_list	*tmp;
	char	*str;

	head = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		str = f(lst->content);
		tmp = ft_lstnew(str);
		if (!tmp)
		{
			if (del && str)
				del(str);
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		var_help(&head, &curr, tmp);
	}
	return (head);
}
