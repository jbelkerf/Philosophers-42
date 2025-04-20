/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/20 13:43:53 by jbelkerf         ###   ########.fr       */
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

long	get_timestamp(t_philo *philo)
{
	struct timeval	time_now;
	time_t			current_time;

	gettimeofday(&time_now, NULL);
	current_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return ((current_time - philo->data->start_time));
}

void	set_forks(t_philo *philo)
{
	int	philo_num;

	philo_num = philo->philo_matricule;
	philo->first_fork.fork = &(philo->data->forks[philo_num]);
	philo->first_fork.number = philo_num;
	if (philo_num == philo->data->number_of_philos - 1)
	{
		philo->second_fork.fork = &(philo->data->forks[0]);
		philo->second_fork.number = 0;
	}
	else
	{
		philo->second_fork.fork = &(philo->data->forks[philo_num + 1]);
		philo->second_fork.number = philo_num + 1;
	}
}


void	precise_sleep(time_t time_to_wait)
{
	time_t	time;
	int		scale;

	time = 0;
	scale = 100;
	while (time < time_to_wait)
	{
		usleep(scale);
		time += scale;
	}
}
