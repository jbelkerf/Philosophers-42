/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:32:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/29 20:22:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	lock(&(philo->data->death_spreed.mutex));
	philo->data->death_spreed.value = 1;
	unlock(&(philo->data->death_spreed.mutex));
	lock(&(philo->data->print));
	printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
	unlock(&(philo->data->print));
}

void	set_death_flag(t_data *data)
{
	lock(&(data->death_spreed.mutex));
	data->death_spreed.value = 1;
	unlock(&(data->death_spreed.mutex));
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	int		number_of_philos;
	time_t	last_meal;
	time_t	to_die;

	philos = arg;
	to_die = philos[0].data->time_to_die;
	number_of_philos = philos[0].data->number_of_philos;
	while (1337)
	{
		i = 0;
		while (i < number_of_philos)
		{
			lock(&(philos[i].last_meal.mutex));
			last_meal = get_current_time() - philos[i].last_meal.value;
			unlock(&(philos[i].last_meal.mutex));
			if (last_meal > to_die)
				return (die(&philos[i]), NULL);
			if (max_meals(philos))
				return (set_death_flag(philos[0].data), NULL);
			i++;
		}
	}
	return (NULL);
}
