/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 18:43:48 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/28 18:43:48 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

void	philo_sleep(int duration)
{
	static _Thread_local struct timeval	curr;
	static _Thread_local struct timeval	end;

	if (duration <= 0)
		return ;
	gettimeofday(&curr, NULL);
	end.tv_sec = curr.tv_sec + (duration / 1000);
	end.tv_usec = curr.tv_usec + ((duration % 1000) * 1000);
	if (end.tv_usec > 1000 * 1000)
	{
		end.tv_usec -= 1000 * 1000;
		end.tv_sec += 1;
	}
	if (duration > SLEEP_THRESHOLD)
	{
		usleep((duration - SLEEP_THRESHOLD) * 1000);
		gettimeofday(&curr, NULL);
	}
	while (curr.tv_sec != end.tv_sec)
		gettimeofday(&curr, NULL);
	while (curr.tv_usec < end.tv_usec && curr.tv_sec == end.tv_sec)
		gettimeofday(&curr, NULL);
}

void	philo_dine(t_philo *philo, t_args *delay)
{
	pthread_mutex_lock(&philo->forks[philo->forkid[0]]);
	print_philo(philo, delay, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->forkid[1]]);
	print_philo(philo, delay, "has taken a fork");
	philo->last_meal = print_philo(philo, delay, "is eating");
	delay->table += 1;
	philo_sleep(delay->digest);
	pthread_mutex_unlock(&philo->forks[philo->forkid[0]]);
	print_philo(philo, delay, "has let go of a fork");
	pthread_mutex_unlock(&philo->forks[philo->forkid[1]]);
	print_philo(philo, delay, "has let go of a fork");
	delay->forklist[philo->forkid[0]] = 0;
	delay->forklist[philo->forkid[1]] = 0;
	print_philo(philo, delay, "is sleeping");
	philo_sleep(delay->sleep);
}

int	call_waiter(t_philo *philo, t_args *delay)
{
	int	granted;

	granted = 0;
	pthread_mutex_lock(philo->waiter);
	if (!delay->deathflag
		&& delay->headcount >= 2
		&& !delay->forklist[philo->forkid[0]]
		&& !delay->forklist[philo->forkid[1]]
		&& delay->table < delay->half
		&& philo->rule == delay->rule)
	{
		delay->forklist[philo->forkid[0]] = 1;
		delay->forklist[philo->forkid[1]] = 1;
		granted = 1;
	}
	pthread_mutex_unlock(philo->waiter);
	return (granted && !delay->deathflag);
}

void	philo_done(t_philo *philo, t_args *delay)
{
	print_philo(philo, delay, "is done");
	delay->done += 1;
	philo->done = 1;
}

void	think_too_hard(t_philo *philo, t_args *delay)
{
	static _Thread_local int			i;
	static _Thread_local int			lock;
	static _Thread_local int			was_thinking;
	static _Thread_local struct timeval	curr;
	static _Thread_local struct timeval	meal;

	i = 0;
	was_thinking = 0;
	while (!delay->deathflag && (!delay->diet_set || i < delay->diet))
	{
		gettimeofday(&curr, NULL);
		meal = philo->last_meal;
		if (timeval_diff(curr, meal) < delay->starve)
			lock = call_waiter(philo, delay);
		if (!lock && !was_thinking)
			print_philo(philo, delay, "is thinking");
		was_thinking = 1;
		if (!lock)
			continue ;
		philo_dine(philo, delay);
		was_thinking = 0;
		i += (lock && delay->diet_set);
	}
	philo_done(philo, delay);
}
