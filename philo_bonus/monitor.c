/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:32:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 21:14:15 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
}

void	unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;
	time_t	last_meal;
	time_t	to_die;

	philo = arg;
	//usleep(100);
	
	to_die = philo->data->time_to_die;
	i = 0;
	while (1337)
	{
		last_meal = get_current_time() - getter(&(philo->last_meal));
		//printf("last meal %ld\n", last_meal);
		if (last_meal >= to_die)
		{
			sem_wait(philo->data->print.sem);
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
			sem_post(philo->data->death_spreed.sem);
			return NULL;
		}
		usleep(10);
	}
}
