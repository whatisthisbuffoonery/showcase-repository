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

static t_list	*ft_lstnew_help(void *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->next = NULL;
	a->content = content;
	return (a);
}

static void	ft_lstdelone_help(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	free(lst);
}

static void	ft_lstclear_help(t_list **lst, void (*del)(void *))
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
		tmp = ft_lstnew_help(str);
		if (!tmp)
		{
			if (del && str)
				del(str);
			ft_lstclear_help(&head, del);
			return (NULL);
		}
		lst = lst->next;
		var_help(&head, &curr, tmp);
	}
	return (head);
}
