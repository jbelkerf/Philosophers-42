/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:32:23 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/21 13:03:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	time_t	last_meal;
	time_t	to_die;
	int		matricule;

	philo = arg;
	to_die = philo->data->time_to_die;
	while (1337)
	{
		last_meal = get_current_time() - get_sem(&(philo->data->last_meal));
		if (last_meal >= to_die)
		{
			matricule = philo->philo_matricule;
			sem_wait(philo->data->print.sem);
			printf("%ld %d died\n", get_timestamp(philo), matricule + 1);
			sem_post(philo->data->death_spreed.sem);
			return (NULL);
		}
		usleep(10);
	}
}
