/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/25 13:03:06 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	int	matricule;

	matricule = philo->philo_matricule;
	if (matricule % 2 == 0 )
	{
		pthread_mutex_lock(philo->first_fork.fork);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
		pthread_mutex_lock(philo->second_fork.fork);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
	}
	else
	{
		pthread_mutex_lock(philo->second_fork.fork);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
		pthread_mutex_lock(philo->first_fork.fork);
		printf("%ld %d has taken a fork\n", get_timestamp(philo), matricule);
	}
}

void	philo_eat(t_philo *philo)
{
	struct timeval	time_now;

	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %d is eating\n", get_timestamp(philo), philo->philo_matricule);
	pthread_mutex_unlock(&(philo->data->print));
	gettimeofday(&time_now, NULL);
	philo->last_meal = (time_now.tv_usec / 1000) + (time_now.tv_sec * 1000);
	precise_sleep(philo->data->time_to_eat);
	philo->number_of_meals++;
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %d is sleeping\n", get_timestamp(philo), philo->philo_matricule);
	pthread_mutex_unlock(&(philo->data->print));
	precise_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%ld %d is thinking\n", get_timestamp(philo), philo->philo_matricule);
	pthread_mutex_unlock(&(philo->data->print));
}

void	give_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork.fork);
	pthread_mutex_unlock(philo->second_fork.fork);
}
