
#include "libft.h"

t_list	*ft_lstnew_chk(void *content, int (*chk)(void *), void (*del)(void *))
{
	t_list	*a;

	if (chk && chk(content))
		return (NULL);
	a = malloc(sizeof(t_list));
	if (!a)
	{
		if (del)
			del(content);
		return (NULL);
	}
	a->next = NULL;
	a->content = content;
	return (a);
}
