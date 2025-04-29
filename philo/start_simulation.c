/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/29 12:24:44 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_routine(t_philo *philo, char *action)
{
	lock(&(philo->data->death_spreed.mutex));
	if (philo->data->death_spreed.value)
	{
		unlock(&(philo->data->death_spreed.mutex));
		return ;
	}
	unlock(&(philo->data->death_spreed.mutex));
	lock(&(philo->data->print));
	printf("%ld %d %s\n", get_timestamp(philo), philo->philo_matricule, action);
	unlock(&(philo->data->print));
}

void	*routine(void *param)
{
	t_philo			*philo;

	philo = param;
	philo->last_meal = get_current_time();
	while (1337)
	{
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
		lock(&(philo->data->death_spreed.mutex));
		if (philo->data->death_spreed.value)
		{
			unlock(&(philo->data->death_spreed.mutex));
			return (NULL);
		}
		unlock(&(philo->data->death_spreed.mutex));
	}
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int				i;
	pthread_t		*tids;

	i = -1;
	philos[0].data->start_time = get_current_time();
	tids = philos->data->tids;
	while (++i < philos[0].data->number_of_philos)
	{
		if (i % 2 == 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	}
	i = -1;
	while (++i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
		pthread_join(philos[0].data->tids[i++], NULL);
}
