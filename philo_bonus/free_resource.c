/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 18:36:48 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	destroy_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

void	free_resources(t_philo *philos)
{
	sem_unlink(philos[0].data->death_spreed.path);
	sem_unlink(philos[0].data->print.path);
	sem_unlink(philos[0].data->forks.path);
	free(philos[0].data->pids);
	free(philos[0].data);
	free(philos);
}
