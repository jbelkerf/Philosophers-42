/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:41:17 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/29 20:37:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_spreed(t_data *data)
{
	lock(&(data->death_spreed.mutex));
	if (data->death_spreed.value)
	{
		unlock(&(data->death_spreed.mutex));
		return (1);
	}
	unlock(&(data->death_spreed.mutex));
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
	return (0);
}
