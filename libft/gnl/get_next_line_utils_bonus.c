/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 02:10:01 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/26 19:18:05 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//void	ft_putnbr(int n);

static void	refresh_buffer_b(t_var *file, int fd, int *done)
{
	if (fd >= 0)
		file->lim = read(fd, file->buf, BUFFER_SIZE);
	file->count = 0;
	if (fd < 0 || file->lim < 0)
	{
		*done = -1;
		file->lim = 0;
	}
	else if (!file->lim)
		*done = 1;
}

char	*read_buf_b(t_var *file, int fd, int *done)
{
	ssize_t	i;
	ssize_t	k;
	char	*ret;

	k = -1;
	if (file->count >= file->lim)
		refresh_buffer_b(file, fd, done);
	if (file->lim < 1)
		return (NULL);
	i = file->count;
	while (file->count < file->lim && file->buf[file->count] != '\n')
		file->count ++;
	*done = (file->count < file->lim && file->buf[file->count] == '\n');
	file->count += *done;
	ret = malloc(((file->count - i) + 1) * sizeof(char));
	if (!ret)
		return ((*done = -1), NULL);
	while (i + ++k < file->count)
		ret[k] = file->buf[i + k];
	ret[k] = '\0';
	return (ret);
}

/*
static void probe(int n)
{	
	write(1, "node: ", 6);
	ft_putnbr(i);
	write(1, "\n", 1);
}
*/

int	gnl_new_b(t_gnllist **lst, char *ret, int i)
{
	t_gnlnode	*new;

	new = malloc(sizeof(t_gnlnode));
	if (!new)
		return (1);
	new->str = ret;
	new->next = NULL;
	if (*lst)
		(*lst)->tail->next = new;
	if (!*lst)
	{
		*lst = malloc(sizeof(t_gnllist));
		if (!*lst)
			return ((free(new)), 1);
		(*lst)->total = 0;
		(*lst)->head = new;
	}
	while (ret[i])
		i ++;
	(new)->str_len = i;
	(*lst)->tail = new;
	(*lst)->total += i;
	return (0);
}

char	*gnl_shove_b(t_gnllist *lst)
{
	int			i;
	int			k;
	int			count;
	t_gnlnode	*curr;
	char		*ret;

	curr = lst->head;
	i = 0;
	ret = malloc((lst->total + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (curr)
	{
		k = -1;
		count = curr->str_len;
		while (++k < count)
			ret[i + k] = curr->str[k];
		i += k;
		curr = curr->next;
	}
	ret[i] = '\0';
	return (ret);
}

void	gnl_cleanup_b(t_gnllist *lst, char **ret, t_var *file, int done)
{
	t_gnlnode	*curr;
	t_gnlnode	*tmp;

	if (lst)
	{
		curr = lst->head;
		while (curr)
		{
			if (curr->str && curr->str != *ret)
				free(curr->str);
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
		free(lst);
	}
	if (done < 0)
	{
		if (*ret)
			free(*ret);
		file->count = 0;
		file->lim = 0;
		*ret = NULL;
	}
}
