/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:18:52 by achew             #+#    #+#             */
/*   Updated: 2025/12/02 14:42:02 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	t_list	*next_node;
	int		count;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		next_node = current->next;
		count++;
		current = next_node;
	}
	return (count);
}
