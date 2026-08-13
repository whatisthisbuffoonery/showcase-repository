/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:49 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 21:23:06 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

int	timeval_diff(struct timeval src1, struct timeval src2)
{
	static _Thread_local struct timeval	curr;
	static _Thread_local int			carry;

	if (src1.tv_sec < src2.tv_sec)
		return (INT_MAX);
	carry = (src1.tv_usec < src2.tv_usec);
	if (carry)
		src1.tv_usec += 1000 * 1000;
	curr.tv_usec = src1.tv_usec - src2.tv_usec;
	curr.tv_sec = (src1.tv_sec - src2.tv_sec) - carry;
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}
