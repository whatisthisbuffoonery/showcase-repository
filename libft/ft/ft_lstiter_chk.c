
#include "libft.h"

int	ft_lstiter_chk(t_list *lst, void (*f)(void *), int (*chk)(void *))
{
	if (!f || !lst)
		return (1);
	while (lst)
	{
		f(lst->content);
		if (chk && chk(lst->content))
			return (1);
		lst = lst->next;
	}
	return (0);
}
