/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/16 11:01:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

void	free_resources(t_philo *philos)
{
	sem_close(philos->data->death_spreed.sem);
	sem_close(philos->data->forks.sem);
	sem_close(philos->data->print.sem);
	sem_close(philos->data->max_meals.sem);
	//!
	sem_unlink(philos->data->death_spreed.path);
	sem_unlink(philos->data->print.path);
	sem_unlink(philos->data->forks.path);
	sem_unlink(philos->data->max_meals.path);
	free(philos[0].data->pids);
	free(philos[0].data);
	free(philos);
}
