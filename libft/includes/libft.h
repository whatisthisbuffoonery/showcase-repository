/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 04:45:36 by dthoo             #+#    #+#             */
/*   Updated: 2026/04/11 23:29:58 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

//if you are including math.h, include it before this header
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

//# ifdef FT_LIST

typedef struct s_list
{
	void			*content;
	int				num;
	struct s_list	*next;
}					t_list;

t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_lstiter_chk(t_list *lst, void (*f)(void *), int (*chk)(void *));
t_list			*ft_lstnew_chk(void *content, int (*chk)(void *),
					void (*del)(void *));

//# endif

//# ifdef FT_PRINTF

typedef enum s_pf_type
{
	str,
	op,
	nil
}	t_pf_type;

typedef struct s_pf_flags
{
	char			plus_space;
	char			minus_zero;
	char			hex;
	char			precision_set;
	int				width;
	int				precision;
}					t_pf_flags;

typedef struct s_pf_q
{
	struct s_pf_q		*next;
	char				*str;
	t_pf_flags			*flags;
	t_pf_type			type;
	char				arg;
}						t_pf_q;

int				ft_printf(const char *format, ...);

char			*gnl(int fd);
char			*gnl_b(int fd);

//# endif

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isquote(int c);
int				ft_ishex(int c);
int				ft_isspace(int c);

int				ft_abs(int n);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				min2(int a, int b);
int				max2(int a, int b);

int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(char *a, char *b);
int				ft_atoi(const char *nptr);
int				ft_atoi_ind(const char *nptr, int *index);
unsigned int	ft_atohu_ind(char *s, int *index, int i);

int				ft_ptrlen(char **a);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);

char			*ft_itoa(int n);
char			*ft_ftoa(float src);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *src, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char			**split_cleanup(char **ret);

char			**ft_split(char const *s, char c);
char			**parsed_argsplit(char *s);

void			ht_init(char *ht, char *src);
void			*ft_calloc(size_t nmemb, size_t size);
void			*malloc_cond(void **dst, size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_intset(int *dst, int c, size_t n);

void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_bzero(void *s, size_t n);

void			ft_swap(int *a, int *b);
void			ft_swapf(float *a, float *b);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int src);
void			ft_putstr(char *a);
void			ft_putchar(char n);

float			minf(float a, float b);
float			absf(float a);

#endif
