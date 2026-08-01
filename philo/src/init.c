/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:46 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:46 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

//gettimeofday can't really fail
int	start_timeval(t_args *delay, t_philo *philos)
{
	int	i;

	if (gettimeofday(&delay->start, NULL))
		return (-1);
	i = 0;
	while (i < delay->headcount)
		philos[i++].last_meal = delay->start;
	if (delay->headcount < 1)
		return (-1);
	return (1);
}

//get run func to set its own forkid
int	init_philo(
		t_philo **philos,
		pthread_t **threads,
		t_args *delay,
		t_mutex_box *mutexes)
{
	int	i;

	if (!malloc_cond((void **) threads, delay->headcount * sizeof(pthread_t))
		|| !malloc_cond((void **) philos, delay->headcount * sizeof(t_philo)))
		return (-1);
	i = 0;
	delay->philos = *philos;
	while (i < delay->headcount)
	{
		(*philos)[i].waiter = &mutexes->waiter;
		(*philos)[i].print = &mutexes->print;
		(*philos)[i].forks = mutexes->forks;
		(*philos)[i].delay = delay;
		(*philos)[i].philoid = i;
		if (pthread_create(&(*threads)[i], NULL, run, &(*philos)[i]))
		{
			while (i-- > 0)
				pthread_join((*threads)[i], NULL);
			free(*threads);
			*threads = NULL;
			return (-1);
		}
		i ++;
	}
	return (0);
}

void	maint_cleanup(t_maint *maint, int size)
{
	int	i;

	if (maint->do_not_cleanup)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_join(maint->threads[i], NULL);
		i ++;
	}
	free(maint->threads);
	maint->do_not_cleanup = 1;
	pthread_join(maint->tabler, NULL);
}

int	init_maint(t_maint *dst, t_args *delay, t_philo *philos)
{
	int	i;
	int	k;

	ft_memset(dst, 0, sizeof(t_maint));
	dst->size = (delay->headcount / THREAD_LOAD)
		+ (delay->headcount % THREAD_LOAD != 0);
	if (!malloc_cond((void **) &dst->threads, dst->size * sizeof(pthread_t))
		|| pthread_create(&dst->tabler, NULL, philo_table, delay))
	{
		free(dst->threads);
		dst->do_not_cleanup = 1;
		return (1);
	}
	i = 0;
	while (i < dst->size)
	{
		k = i * THREAD_LOAD;
		if (pthread_create(&dst->threads[i], NULL, monitor_philos, &philos[k]))
		{
			maint_cleanup(dst, i);
			return (1);
		}
		i ++;
	}
	return (0);
}

int	init_mutexes(t_mutex_box *dst, t_args *delay)
{
	int	i;
	int	size;

	size = delay->headcount;
	ft_memset(dst, 0, sizeof(t_mutex_box));
	if (!malloc_cond((void **) &dst->forks, size * sizeof(pthread_mutex_t)))
		return (1);
	i = 0;
	while (i < size)
		pthread_mutex_init(&dst->forks[i++], NULL);
	pthread_mutex_init(&dst->print, NULL);
	pthread_mutex_init(&dst->waiter, NULL);
	return (0);
}
