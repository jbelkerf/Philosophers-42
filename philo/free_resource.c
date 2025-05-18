/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/29 11:51:19 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo_mutex(t_philo *philos)
{
	int	i;
	t_mutex *forks;

	forks = philos->data->forks;
	i = 0;
	while (i < philos->data->number_of_philos)
	{
		pthread_mutex_destroy(&(forks[i]));
		pthread_mutex_destroy(&(philos[i].last_meal.mutex));
		pthread_mutex_destroy(&(philos[i].number_of_meals.mutex));
		i++;
	}
}

void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

void	free_resources(t_philo *philos)
{
	destroy_philo_mutex(philos);
	destroy_mutex(&(philos[0].data->print));
	destroy_mutex(&(philos[0].data->death_spreed.mutex));
	free(philos[0].data->forks);
	free(philos[0].data->tids);
	free(philos[0].data);
	free(philos);
}
