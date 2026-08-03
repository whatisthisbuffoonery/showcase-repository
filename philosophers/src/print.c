/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:48 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:48 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

/*
struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg)
{
	static _Thread_local struct timeval	display;
	static _Thread_local struct timeval	src;
	static _Thread_local int			ms;

	gettimeofday(&display, NULL);
	src = philo->last_meal;
	ms = timeval_diff(display, delay->start);
	pthread_mutex_lock(philo->print);
	if (!((msg[0] != 'd' && timeval_diff(display, src) >= delay->starve)
		|| delay->deathflag))
	{
		ft_putnbr(ms);
		ft_putchar(' ');
		ft_putnbr(philo->philoid + 1);
		ft_putchar(' ');
		ft_putstr(msg);
		ft_putchar('\n');
	}
	pthread_mutex_unlock(philo->print);
	return (display);
}
*/

//mutex stays locked on death
int	check_death(t_philo *philo, t_args *delay, char *msg)
{
	pthread_mutex_lock(philo->print);
	if (delay->deathflag)
	{
		pthread_mutex_unlock(philo->print);
		return (1);
	}
	else if (msg[0] == 'd')
	{
		delay->deathflag = 1;
		return (0);
	}
	pthread_mutex_unlock(philo->print);
	return (0);
}

int	set_buf(char *buf, t_philo *philo, char *msg, int ms)
{
	static _Thread_local int	i;

	i = bufnum(buf, ms, BUFLEN);
	if (i + 1 + 1 < BUFLEN)
	{
		buf[i++] = ' ';
		i += bufnum(&buf[i], philo->philoid + 1, BUFLEN - i);
		if (i + 1 < BUFLEN)
			buf[i++] = ' ';
	}
	ft_strlcpy(&buf[i], msg, BUFLEN - i);
	i = 0;
	while (buf[i])
		i ++;
	return (i);
}

struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg)
{
	static _Thread_local char			buf[BUFLEN];
	static _Thread_local struct timeval	display;
	static _Thread_local struct timeval	src;
	static _Thread_local int			ms;
	static _Thread_local int			i;

	gettimeofday(&display, NULL);
	src = philo->last_meal;
	ms = timeval_diff(display, delay->start);
	i = set_buf(buf, philo, msg, ms);
	buf[i] = '\n';
	if (check_death(philo, delay, msg))
		return (display);
	else if (!(msg[0] != 'd' && timeval_diff(display, src) >= delay->starve))
		write(1, buf, i + 1);
	if (msg[0] == 'd')
		pthread_mutex_unlock(philo->print);
	return (display);
}

//I will actually make up my mind on cmp funcs after making bad ones fmllll
//move curr back to local
