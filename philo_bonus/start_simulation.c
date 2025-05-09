/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 18:51:08 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_routine(t_philo *philo, char *action)
{
	if (get_sem_value(&(philo->data->death_spreed)))
		return ;
	sem_wait(philo->data->print.sem);
	printf("%ld %d %s\n", get_timestamp(philo), philo->philo_matricule, action);
	sem_post(philo->data->print.sem);
}

void	*routine(void *param)
{
	t_philo	*philo;

	printf("routine philo num\n");
	philo = param;
	setter(&(philo->last_meal), get_current_time());
	while (1337)
	{
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (get_sem_value(&(philo->data->death_spreed)))
			return (NULL);
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, routine, philo);
	monitor(philo);
	pthread_join(tid, NULL);
	exit(1);
}

void	start_simulation(t_philo *philos)
{
	int		i;

	i = -1;
	philos[0].data->start_time = get_current_time();
	while (++i < philos[0].data->number_of_philos)
	{
		philos->data->pids[i] = fork();
		if (philos->data->pids[i] == 0)
		{
			start_philo(&(philos[i]));
		}
	}
	i = -1;
	// sleep(10);
	while (++i < philos[0].data->number_of_philos)
	{
		printf("pid %d --> %d\n",i, philos->data->pids[i]);
		waitpid(philos->data->pids[i], NULL, 0);
	}
}
