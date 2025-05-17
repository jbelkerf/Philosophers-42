/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/17 19:54:45 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_routine(t_philo *philo, char *action)
{
	int	matricule;

	matricule = philo->philo_matricule + 1;
	if (getter(&(philo->data->death_spreed)))
		return ;
	lock(&(philo->data->print));
	printf("%ld %d %s\n", get_timestamp(philo), matricule, action);
	unlock(&(philo->data->print));
}

void	*routine(void *param)
{
	t_philo			*philo;

	philo = param;
	setter(&(philo->last_meal), get_current_time());
	while (1337)
	{
		ft_think(philo);
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
		if (getter(&(philo->data->death_spreed)))
			return (NULL);
	}
	return (NULL);
}

void	handle_one_philo(t_philo *philo)
{
	lock(philo->first_fork.fork);
	log_routine(philo, "has taken a fork");
	precise_sleep(philo, philo->data->time_to_die);
	log_routine(philo, "died");
}

void	*start_simulation(t_philo *philos)
{
	int				i;
	pthread_t		*tids;
	pthread_t		monitor_tid;

	i = -1;
	philos[0].data->start_time = get_current_time();
	if (philos->data->number_of_philos == 1)
		return (handle_one_philo(&(philos[0])), NULL);
	tids = philos->data->tids;
	while (++i < philos[0].data->number_of_philos)
		if (i % 2 == 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	i = -1;
	while (++i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	}
	pthread_create(&monitor_tid, NULL, monitor, philos);
	pthread_join(monitor_tid, NULL);
	i = 0;
	while (i < philos[0].data->number_of_philos)
		pthread_join(philos[0].data->tids[i++], NULL);
	return (NULL);
}
