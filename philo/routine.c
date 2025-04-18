/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/18 11:08:10 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_mutex *f_fork, t_mutex *s_fork, t_philo *philo)
{
	int	matricule;

	matricule = philo->philo_matricule;
	pthread_mutex_lock(f_fork);
	pthread_mutex_lock(s_fork);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
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

void	give_fork(t_mutex *f_fork, t_mutex *s_fork)
{
	pthread_mutex_unlock(f_fork);
	pthread_mutex_unlock(s_fork);
}
