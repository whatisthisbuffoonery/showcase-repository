/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:52 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/26 19:17:51 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		gnl_new_b(t_gnllist **lst, char *ret, int i);
void	gnl_cleanup_b(t_gnllist *lst, char **ret, t_var *file, int done);
char	*gnl_shove_b(t_gnllist *lst);
char	*read_buf_b(t_var *file, int fd, int *done);

static void	gnl_file_management(t_stash *stash, t_var *file, int fd, int flag)
{
	if (flag)
	{
		file->buf = stash->buf[fd];
		file->count = stash->count[fd];
		file->lim = stash->lim[fd];
	}
	else
	{
		stash->count[fd] = file->count;
		stash->lim[fd] = file->lim;
	}
}

char	*gnl_b(int fd)
{
	static t_stash	stash;
	t_var			file;
	t_gnllist		*lst;
	char			*ret;
	int				done;

	done = 0;
	lst = NULL;
	ret = NULL;
	if (fd < 0 || fd > 1023)
		return (NULL);
	gnl_file_management(&stash, &file, fd, 1);
	while (!done)
	{
		ret = read_buf_b(&file, fd, &done);
		if (!ret)
			break ;
		if (gnl_new_b(&lst, ret, 0))
			done = -1;
	}
	if (done == 1 && lst)
		ret = gnl_shove_b(lst);
	gnl_cleanup_b(lst, &ret, &file, done);
	gnl_file_management(&stash, &file, fd, 0);
	return (ret);
}

/*
#include <fcntl.h>

void ft_putnbr(int n)
{
	int t = 1;
	char a;
	while (n / t > 9)
		t *= 10;
	while (t)
	{
		a = ((n / t) % 10) + 48;
		write(1, &a, 1);
		t /= 10;
	}
	write(1, "\n", 1);
}

void ft_putstr(char *a, int flag)
{
	int i = 0;
	if (!a)
	{
		ft_putstr("(null)\n", 0);
		return ;
	}
	while (a[i])
		i ++;
	write(1, a, i);
	if (flag)
	{
		if (a[i - 1] == '\n')
			write(1, "nl\n", 3);
		else
			write(1, "|eof|\n", 6);
	}
}

int ft_strlen(char *a)
{
	int i = 0;
	while (a && a[i])
		i ++;
	return (i);
}

void read_file(int fd, size_t lines)
{
	char *a;
	if (!lines)
		lines = -1;
	while (lines--)
	{
		a = get_next_line(fd);
		
		if (a && a[0] == '\n')
			ft_putstr("nl\n", 0);
		if (a && a[0] == '\0')
			ft_putstr(".\n", 0);
		
		ft_putstr(a, 1);
		//ft_putnbr(ft_strlen(a));
		if (!a)
			return ;
		free(a);
	}
}

int main(int c, char **v)
{
	if (c < 2)
		return (1);
	ft_putnbr(BUFFER_SIZE);
	(void) v;
	int fd = open(v[1], O_RDONLY);
	if (fd < 0)
		return (1);
	read_file(fd, 0);
//	close(fd);
//	fd = open("not_a_file.txt", O_WRONLY);
//	fd = -100;
//	read_file(fd, 0);
//	fd = open(v[1], O_RDONLY);
//	if (fd < 0)
//		return (0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	read_file(fd, 0);
	close(fd);
//	write(1, "\n", 1);
}
*/
