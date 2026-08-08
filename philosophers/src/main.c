/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:47 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:47 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

int	init_delay(t_args *delay, char **v)
{
	ft_memset(delay, 0, sizeof(t_args));
	delay->headcount = ft_atoi(v[1]);
	delay->starve = ft_atoi(v[2]);
	delay->digest = ft_atoi(v[3]);
	delay->sleep = ft_atoi(v[4]);
	if (v[5])
	{
		delay->diet_set = 1;
		delay->diet = ft_atoi(v[5]);
	}
	delay->forklist = malloc(delay->headcount * sizeof(char));
	if (!delay->forklist)
		return (1);
	ft_memset(delay->forklist, 0, delay->headcount * sizeof(char));
	delay->half = delay->headcount / 2;
	return (0);
}

//reject negative
int	arg_check(t_args *delay, int c, char **v)
{
	int	i;
	int	k;

	if (c != 5 && c != 6)
		return (1);
	k = 1;
	while (v[k])
	{
		i = 0;
		while (v[k][i])
		{
			if (v[k][i] < '0' || v[k][i] > '9')
				return (1);
			i ++;
		}
		k ++;
	}
	return (init_delay(delay, v));
}

void	headcount_cleanup(
		t_philo *philos,
		pthread_t *threads,
		t_args *delay,
		t_mutex_box *mutexes)
{
	int	i;

	i = 0;
	while (philos && threads && i < delay->headcount)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < delay->headcount)
		pthread_mutex_destroy(&mutexes->forks[i++]);
	pthread_mutex_destroy(&mutexes->print);
	pthread_mutex_destroy(&mutexes->waiter);
	free(philos);
	free(threads);
	free(mutexes->forks);
	free(delay->forklist);
}

int	macro_check(void)
{
	int	ret;

	ret = 0;
	if (THREAD_LOAD <= 0 || THREAD_LOAD > INT_MAX)
	{
		ret ++;
		write(2,
			"THREAD_LOCAL needs to be a positive integer greater than zero\n",
			62);
	}
	if (SLEEP_THRESHOLD < 0 || SLEEP_THRESHOLD > INT_MAX)
	{
		ret ++;
		write(2,
			"SLEEP_THRESHOLD cannot be a negative or overflowing integer\n",
			60);
	}
	return (0);
}

//delay has like 5 timevals
//start can be 1, 0, -1
//being stuck with blocking mutex lock means:
//we have to use main thread to update deathflag and print death message
//so the philos do not check for starvation
//usleep 9000
int	main(int c, char **v)
{
	t_args		delay;
	pthread_t	*threads;
	t_maint		maint;
	t_philo		*philos;
	t_mutex_box	mutexes;

	threads = NULL;
	philos = NULL;
	delay.startflag = 0;
	if (macro_check() || arg_check(&delay, c, v)
		|| init_mutexes(&mutexes, &delay))
	{
		free(delay.forklist);
		return (1);
	}
	if (init_philo(&philos, &threads, &delay, &mutexes)
		|| init_maint(&maint, &delay, philos))
		delay.startflag = -1;
	else
		delay.startflag = start_timeval(&delay, philos);
	maint_cleanup(&maint, maint.size);
	headcount_cleanup(philos, threads, &delay, &mutexes);
}
