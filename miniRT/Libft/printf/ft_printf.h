/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:40:54 by achew             #+#    #+#             */
/*   Updated: 2025/12/18 16:56:07 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h> //for write()
# include <stdint.h> //for uintptr_t
# include <stdarg.h> //for va_*
# include <stdlib.h> //for malloc

# define SPECIFIER "cspdiuxX%"
# define FLAGS "-+ #0"
# define DIGITS "0123456789"
# define HEX_L "0123456789abcdef"
# define HEX_U "0123456789ABCDEF"

typedef enum e_type
{
	character = 'c',
	string = 's',
	pointer = 'p',
	decimal = 'd',
	integer = 'i',
	unsigned_decimal = 'u',
	hexadecimal_lower = 'x',
	hexadecimal_upper = 'X',
	percent = '%'
}	t_type;

typedef union u_data
{
	char			*s;
	void			*p;
	long long		d;
	unsigned int	u;
}	t_data;

typedef enum e_flags
{
	no_flags = 0,
	left_justify = 1 << 0,
	forced_sign = 1 << 1,
	forced_space = 1 << 2,
	form_change = 1 << 3,
	zero_padding = 1 << 4
}	t_flags;

typedef struct s_arg
{
	t_type	type;
	t_data	data;
	int		flags;
	int		min_width;
	int		precision;
	int		data_width;
	int		zero_padded_width;
}	t_arg;

int		ft_printf(const char *str, ...);
int		*is_fmt(const char *str);
t_arg	*init_arg(const char *str, int *fmt_len, va_list ap);
int		print_data(t_arg *arg);
int		ft_putchar(char c, int write_char);
int		ft_putstr(char *str, int write_str, t_arg *arg);
int		ft_putnbr(long long nb_ll, int write_nbr, t_arg *arg);
int		putnbr_u(unsigned int nb, int write_nbr, t_arg *arg);
int		putptr(void *ptr, int write_ptr, t_arg *arg);
int		puthex_p(uintptr_t n, char alphacase, int write_hex);
int		puthex_u(unsigned int n, char alphacase, int write_hex, t_arg *arg);
int		ft_atoi(const char *str);
int		add_zero(t_arg *arg, int write_zero, int sign);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
