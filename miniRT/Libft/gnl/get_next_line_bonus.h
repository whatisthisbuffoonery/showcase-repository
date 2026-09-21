/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 13:00:40 by achew             #+#    #+#             */
/*   Updated: 2026/02/01 14:41:31 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*init_array(int size);
void	*ft_memset2(void *b, int c, size_t len);
ssize_t	fill_buffer(char *buffer, int fd, char *stash);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
ssize_t	get_line_len(char *buffer, ssize_t buffer_len);
char	*extend_line(char *line, int fd);
size_t	ft_strlen2(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
