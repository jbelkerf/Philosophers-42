/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:32:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 18:11:04 by jbelkerf         ###   ########.fr       */
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

	printf("monitor philo num");
	philo = arg;
	to_die = philo->data->time_to_die;
	i = 0;
	while (1337)
	{
		last_meal = get_current_time() - getter(&(philo->last_meal));
		if (last_meal > to_die)
		{
			set_sem_value(&(philo->data->death_spreed), 1);
			return (NULL);
		}
	}
	return (NULL);
}
