/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 15:45:03 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_optional(t_philo *philos)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (i < philos[0].data->number_of_philos)
	{
		if (philos[i].number_of_meals < philos[i].data->optional)
			flag = 0;
		i++;
	}
	return (flag);
}

long	get_timestamp(t_philo *philo)
{
	struct timeval	time_now;
	time_t			current_time;

	gettimeofday(&time_now, NULL);
	current_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	//!printf("current time %ld   start time %ld\n", current_time, philo->data->start_time);
	return ((current_time - philo->data->start_time));
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

int	check_die(t_philo *philo)
{
	struct timeval	time_now;
	time_t			time_to_die;
	time_t			time_last_meal;
	time_t			current_time;

	pthread_mutex_lock(&(philo->data->death_spreed.mutex));
	if (philo->data->death_spreed.value)
	{
		pthread_mutex_unlock(&(philo->data->death_spreed.mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->death_spreed.mutex));
	gettimeofday(&time_now, NULL);
	current_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	time_to_die = philo->data->time_to_die;
	time_last_meal = current_time - philo->last_meal;
	if (time_last_meal > time_to_die)
	{
		pthread_mutex_lock(&(philo->data->death_spreed.mutex));
		philo->data->death_spreed.value = 1;
		pthread_mutex_unlock(&(philo->data->death_spreed.mutex));
		return (1);
	}
	return (0);
}
