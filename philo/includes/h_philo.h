/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 18:59:28 by dthoo             #+#    #+#             */
/*   Updated: 2026/07/23 18:59:58 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PHILO_H
# define H_PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdatomic.h>

# ifndef THREAD_LOAD
#  define THREAD_LOAD 1
# endif

# ifndef BUFLEN
#  define BUFLEN 50
# endif

# ifndef SLEEPTHRESHOLD
#  define SLEEP_THRESHOLD 40
# endif

typedef _Atomic struct timeval	t_atomic_tv;

typedef struct s_args
{
	struct timeval	start;
	struct s_philo	*philos;
	_Atomic char	*forklist;
	int				digest;
	int				sleep;
	int				starve;
	_Atomic int		table;
	_Atomic int		done;
	_Atomic int		startflag;
	_Atomic int		deathflag;
	int				half;
	int				headcount;
	int				diet;
	int				diet_set;
	_Atomic int		rule;
}					t_args;

typedef struct s_philo
{
	t_atomic_tv		last_meal;
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	t_args			*delay;
	int				forkid[2];
	int				philoid;
	int				rule;
	_Atomic int		done;
}					t_philo;

typedef struct s_maint
{
	pthread_t	*threads;
	pthread_t	tabler;
	int			size;
	int			do_not_cleanup;
}				t_maint;

typedef struct s_mutex_box
{
	pthread_mutex_t	waiter;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}					t_mutex_box;

int				init_philo(
					t_philo **philos,
					pthread_t **threads,
					t_args *delay,
					t_mutex_box *mutexes);

int				init_mutexes(t_mutex_box *dst, t_args *delay);
struct timeval	print_philo(t_philo *philo, t_args *delay, char *msg);
int				start_timeval(t_args *delay, t_philo *philos);

void			*run(void *src);
void			*monitor_philos(void *data);
void			*philo_table(void *data);

int				init_maint(t_maint *dst, t_args *delay, t_philo *philos);
void			maint_cleanup(t_maint *maint, int size);

int				timeval_diff(struct timeval src1, struct timeval src2);

void			think_too_hard(t_philo *philo, t_args *delay);

int				ft_atoi(char *s);
void			*ft_memset(void *dst, int c, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t dsize);
void			*malloc_cond(void **dst, size_t size);
int				bufnum(char *dst, int src, int size);

#endif
