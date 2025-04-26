/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 12:36:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_timestamp(t_philo *philo)
{
	return (get_current_time() - philo->data->start_time);
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
	time_t			start;
	time_t			current;
	struct timeval	s_start;
	struct timeval	s_current;

	gettimeofday(&s_current, NULL);
	current = s_current.tv_sec * 1000 + s_current.tv_usec / 1000;
	start = current;
	while (current < start + time_to_wait)
	{
		usleep(100);
		gettimeofday(&s_current, NULL);
		current = s_current.tv_sec * 1000 + s_current.tv_usec / 1000;
	}
}

time_t	get_current_time(void)
{
	struct timeval	time_now;
	time_t			result;

	gettimeofday(&time_now, NULL);
	result = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return (result);
}

int	dead_spreed(t_data *data)
{
	pthread_mutex_lock(&(data->death_spreed.mutex));
	if (data->death_spreed.value)
	{
		pthread_mutex_unlock(&(data->death_spreed.mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->death_spreed.mutex));
	return (0);
}

int	time_is_over(t_philo *philo)
{
	time_t	time_to_die;
	time_t	time_last_meal;
	time_t	current_time;

	current_time = get_current_time();
	time_to_die = philo->data->time_to_die;
	time_last_meal = current_time - philo->last_meal;
	if (time_last_meal >= time_to_die)
	{
		pthread_mutex_lock(&(philo->data->death_spreed.mutex));
		philo->data->death_spreed.value = 1;
		die(philo);
		pthread_mutex_unlock(&(philo->data->death_spreed.mutex));
		return (1);
	}
	return (0);
}

int	max_meals(t_philo *philos)
{
	int	i;
	int	max_meals;
	int	philos_number;

	if (philos[0].data->optional == -1)
		return (0);
	i = 0;
	max_meals = philos[0].data->optional;
	while (i < philos_number)
	{
		if (philos[i].number_of_meals < max_meals)
			return (0);
		i++;
	}
	return (1);
}

int	should_stoped(t_philo *philo)
{
	t_philo	*philos;

	philos = philo->data->philos;
	//! dead spreed
	if (dead_spreed(philo->data))
		return (1);
	//! time over
	if (time_is_over(philo))
		return (1);
	//! over meal
	if (max_meals(philo->data->philos))
		return (1);
	return (0);
}
