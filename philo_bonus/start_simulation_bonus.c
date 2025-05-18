/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/18 13:04:40 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	setter(&(philo->last_meal), get_current_time());
	if (philo->philo_matricule % 2 == 0)
		ft_sleep(philo);
	while (1337)
	{
		ft_think(philo);
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	pthread_t	tid;

	unified_start(philo);
	pthread_create(&tid, NULL, monitor, philo);
	routine(philo);
	pthread_join(tid, NULL);
	exit(1);
}

void	let_philos_be(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->number_of_philos)
	{
		if (i % 2 == 0)
		{
			philos->data->pids[i] = fork();
			if (philos->data->pids[i] == 0)
				start_philo(&(philos[i]));
		}
	}
	i = -1;
	while (++i < philos->data->number_of_philos)
	{
		if (i % 2 != 0)
		{
			philos->data->pids[i] = fork();
			if (philos->data->pids[i] == 0)
				start_philo(&(philos[i]));
		}
	}
}

void	handle_one_philo(t_philo *philo)
{
	unified_start(philo);
	log_routine(philo, "is thinking");
	sem_wait(philo->data->forks.sem);
	log_routine(philo, "has taken a fork");
	precise_sleep(philo->data->time_to_die);
	log_routine(philo, "died");
}

void	*start_simulation(t_philo *philos)
{
	int			i;
	pthread_t	tid[2];

	i = -1;
	philos->data->start_time = get_current_time() + 3000;
	if (philos->data->number_of_philos == 1)
		return (handle_one_philo(&(philos[0])), NULL);
	let_philos_be(philos);
	if (philos->data->optional != -1)
		pthread_create(&(tid[0]), NULL, watch_fat_philo_meals, philos->data);
	pthread_create(&(tid[1]), NULL, declare_war, philos->data);
	if (philos->data->optional != -1)
		pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	i = 0;
	while (i < philos->data->number_of_philos)
	{
		waitpid(philos->data->pids[i], NULL, 0);
		i++;
	}
	return (NULL);
}
