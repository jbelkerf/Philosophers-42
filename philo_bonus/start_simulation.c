/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 16:52:44 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_routine(t_philo *philo, char *action)
{
	if (getter(&(philo->data->death_spreed)))
		return ;
	sem_wait(philo->data->print.sem);
	printf("%ld %d %s\n", get_timestamp(philo), philo->philo_matricule, action);
	sem_post(philo->data->print.sem);
}

void	*routine(t_philo *philo)
{
	setter(&(philo->last_meal), get_current_time());
	while (1337)
	{
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (getter(&(philo->data->death_spreed)))
			return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int		i;
	pid_t	*pids;

	i = -1;
	philos[0].data->start_time = get_current_time();
	pids = philos->data->pids;
	while (++i < philos[0].data->number_of_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			routine(&(philos[i]));
		}
	}
	i = -1;
	while (wait(NULL) > 0)
	{
	}
}
