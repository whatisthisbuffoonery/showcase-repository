/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:15:13 by dthoo             #+#    #+#             */
/*   Updated: 2025/12/26 18:33:14 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 128

# endif

typedef struct s_stash
{
	char	buf[1024][BUFFER_SIZE];
	ssize_t	count[1024];
	ssize_t	lim[1024];
}			t_stash;

typedef struct s_var
{
	char	*buf;
	ssize_t	count;
	ssize_t	lim;
}			t_var;

typedef struct s_gnlnode
{
	char				*str;
	struct s_gnlnode	*next;
	int					str_len;
}						t_gnlnode;

typedef struct s_gnllist
{
	t_gnlnode			*head;
	t_gnlnode			*tail;
	int					total;
}						t_gnllist;

char	*gnl_b(int fd);

#endif
