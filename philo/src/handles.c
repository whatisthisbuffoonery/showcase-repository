/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:36 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:42 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

int	check_starvation(t_philo *philos, t_args *delay, int max)
{
	static _Thread_local struct timeval	cmp;
	static _Thread_local struct timeval	curr;
	static _Thread_local int			diff_ms;
	static _Thread_local int			max_ms;
	static _Thread_local int			i;

	i = 0;
	max_ms = INT_MIN;
	gettimeofday(&curr, NULL);
	while (i < max && !delay->deathflag)
	{
		cmp = philos[i].last_meal;
		diff_ms = timeval_diff(curr, cmp);
		if (!philos[i].done && diff_ms >= delay->starve)
		{
			pthread_mutex_lock(philos[i].waiter);
			print_philo(&philos[i], delay, "died");
			pthread_mutex_unlock(philos[i].waiter);
		}
		else if (max_ms < diff_ms)
			max_ms = diff_ms;
		i ++;
	}
	return (delay->starve - max_ms);
}

//each thread gets a different philo
//there was a waiter mutex for starvation
void	*monitor_philos(void *data)
{
	static _Thread_local t_philo	*philos;
	static _Thread_local t_args		*delay;
	static _Thread_local int		max;
	static _Thread_local int		diff;

	philos = (t_philo *) data;
	delay = philos[0].delay;
	max = philos[0].philoid + THREAD_LOAD;
	if (max >= delay->headcount)
		max = delay->headcount % THREAD_LOAD;
	else
		max = THREAD_LOAD;
	while (!delay->startflag)
		continue ;
	while (delay->startflag >= 0
		&& !delay->deathflag
		&& delay->done != delay->headcount)
	{
		diff = check_starvation(philos, delay, max);
		if (diff > SLEEP_THRESHOLD)
			usleep((diff - SLEEP_THRESHOLD) * 1000);
	}
	return (NULL);
}

void	*philo_table(void *data)
{
	t_args	*delay;

	delay = (t_args *) data;
	while (!delay->startflag)
		continue ;
	while (!delay->deathflag
		&& delay->done != delay->headcount
		&& delay->startflag > 0)
	{
		if ((delay->rule != 2 && delay->table < delay->half)
			|| (delay->rule == 2 && !delay->table))
			continue ;
		delay->rule += 1;
		if (delay->rule >= 3 - !(delay->headcount % 2))
			delay->rule = 0;
		delay->table = 0;
	}
	return (NULL);
}

void	*run(void *src)
{
	static _Thread_local t_philo	*philo;
	static _Thread_local t_args		*delay;

	philo = (t_philo *) src;
	delay = philo->delay;
	philo->rule = philo->philoid % 2;
	if (philo->philoid == delay->headcount - 1 && delay->headcount % 2)
		philo->rule = 2;
	philo->forkid[0] = philo->philoid;
	philo->forkid[1] = philo->philoid + 1;
	if (philo->forkid[1] >= delay->headcount)
		philo->forkid[1] = 0;
	while (!delay->startflag)
		continue ;
	if (delay->startflag > 0)
		think_too_hard(philo, philo->delay);
	return (NULL);
}
