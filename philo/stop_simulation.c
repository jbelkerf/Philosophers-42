/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:41:17 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 13:48:02 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_philo *philo)
{
	printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
	return (NULL);
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
	if (time_last_meal > time_to_die)
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
	philos_number = philos[0].data->number_of_philos;
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
	if (dead_spreed(philo->data))
		return (1);
	if (time_is_over(philo))
		return (1);
	if (max_meals(philo->data->philos))
		return (1);
	return (0);
}
