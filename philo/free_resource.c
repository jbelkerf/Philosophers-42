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

void	destroy_forks(int number_of_forks, t_mutex *forks)
{
	int	i;

	i = 0;
	while (i < number_of_forks)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
}

void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

void	free_resources(t_philo *philos)
{
	destroy_forks(philos[0].data->number_of_philos, philos[0].data->forks);
	destroy_mutex(&(philos[0].data->print));
	destroy_mutex(&(philos[0].data->death_spreed.mutex));
	free(philos[0].data->forks);
	free(philos[0].data->tids);
	free(philos[0].data);
	free(philos);
}
