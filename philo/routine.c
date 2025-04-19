/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 15:39:10 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_mutex *fork, t_philo *philo)
{
	int	matricule;

	matricule = philo->philo_matricule;
	pthread_mutex_lock(fork);
	printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	time_now;

	printf("%ld %d is eating\n", get_timestamp(philo), philo->philo_matricule);
	philo->number_of_meals++;
	usleep(philo->data->time_to_eat * 1000);
	gettimeofday(&time_now, NULL);
	philo->last_meal = (time_now.tv_usec / 1000) + (time_now.tv_sec * 1000);
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

void	give_fork(t_mutex *fork)
{
	pthread_mutex_unlock(fork);
}
