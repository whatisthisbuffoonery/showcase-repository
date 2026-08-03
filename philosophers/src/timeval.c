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
/*
void	timeval_find_max(struct timeval *max, struct timeval *test)
{
	test->tv_sec = -1;
	test->tv_usec = -1;
	if (test->tv_sec > 0)
		max->tv_sec = -1;
	else
	{
		max->tv_sec = 1;
		max->tv_sec <<= (sizeof(max->tv_sec) * CHAR_BIT) - 1;
		max->tv_sec = ~max->tv_sec;
	}
	if (test->tv_usec > 0)
		max->tv_usec = -1;
	else
	{
		max->tv_usec = 1;
		max->tv_usec <<= (sizeof(max->tv_usec) * CHAR_BIT) - 1;
		max->tv_usec = ~max->tv_usec;
	}
}
*/

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

/*
int	timeval_diff_atomic(struct timeval src1, _Atomic struct timeval src2)
{
	static _Thread_local struct timeval	input;

	input = src2;
	return (timeval_diff(src1, input));
}
*/
