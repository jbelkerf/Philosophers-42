/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 21:18:55 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(int philo_matricule, t_mutex *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("philo %d dkhal\n", philo_matricule);
	pthread_mutex_unlock(print_mutex);
}

long	get_timestamp(t_philo *philo)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec - philo->data->start_time) / 1000);
}

void	set_forks(t_mutex *f, t_mutex *s, t_philo *philo)
{
	int	philo_num;

	philo_num = philo->philo_matricule;
	*f = philo->data->forks[philo_num];
	if (philo_num == philo->data->number_of_philos - 1)
		*s = philo->data->forks[0];
	else
		*s = philo->data->forks[philo_num + 1];
}

void	take_fork(t_mutex *f_fork, t_mutex *s_fork, t_philo *philo)
{
	pthread_mutex_lock(f_fork);
	pthread_mutex_lock(s_fork);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), philo->philo_matricule);
}

void	give_fork(t_mutex *f_fork, t_mutex *s_fork)
{
	pthread_mutex_unlock(f_fork);
	pthread_mutex_unlock(s_fork);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	time_now;

	printf("%ld %d is eating\n", get_timestamp(philo), philo->philo_matricule);
	usleep(philo->data->time_to_eat * 1000);
	gettimeofday(&time_now, NULL);
	philo->last_meal = time_now.tv_usec;
}

void	philo_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_timestamp(philo), philo->philo_matricule);
	usleep(philo->data->time_to_sleep * 1000);
}
void	philo_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_timestamp(philo), philo->philo_matricule);
}

int	check_die(t_philo *philo)
{
	struct timeval	time_now;
	long			time_to_die;
	long			time_last_meal;

	if (philo->data->death_spreeded)
		return (1);
	gettimeofday(&time_now, NULL);
	time_to_die = philo->data->time_to_die * 1000;
	time_last_meal = time_now.tv_usec - philo->last_meal;
	if (time_last_meal > time_to_die)
	{
		philo->data->death_spreeded = 1;
		return (1);
	}
	return (0);
}
