/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_printf.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dthoo <dthoo@student.42singapore.sg>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/11/26 02:17:50 by dthoo			   #+#	  #+#			  */
/*	 Updated: 2025/11/26 06:12:51 by dthoo			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	printf_tokens(const char *format, t_pf_q **q, int size);
int		process(t_pf_q *q, va_list *va);
int		print_strlen(char *a, t_pf_q *q);
void	clear_q(t_pf_q **q);

static int	print_the_printf(t_pf_q *q)
{
	int	total;
	int	curr;
	int	written;

	total = 0;
	while (q)
	{
		curr = print_strlen(q->str, q);
		written = 0;
		while (written < curr)
			written = write(1, q->str + written, curr - written);
		total += curr;
		q = q->next;
	}
	return (total);
}

int	ft_printf(const char *format, ...)
{
	va_list	va;
	t_pf_q	*q;
	int		return_value;

	q = NULL;
	return_value = -1;
	va_start(va, format);
	printf_tokens(format, &q, ft_strlen(format));
	if (q)
		return_value = process(q, &va);
	if (q && !return_value)
		return_value = print_the_printf(q);
	clear_q(&q);
	va_end(va);
	return (return_value);
}
