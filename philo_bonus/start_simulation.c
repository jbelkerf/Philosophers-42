/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 21:14:38 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_routine(t_philo *philo, char *action)
{
	sem_wait(philo->data->print.sem);
	printf("%ld %d %s\n", get_timestamp(philo), philo->philo_matricule, action);
	sem_post(philo->data->print.sem);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	printf("amalk\n");
	increment_flag(&(philo->started));
	setter(&(philo->last_meal), get_current_time());
	while (1337)
	{
		take_forks(philo);
		ft_eat(philo);
		give_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	pthread_t	tid;

	printf("waaaaa\n");
	pthread_create(&tid, NULL, routine, philo);
	monitor(philo);
	pthread_join(tid, NULL);
	exit(1);
}

void *watch_fat_philo_meals(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = arg;
	while (i < data->number_of_philos)
	{
		sem_wait(data->max_meals.sem);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		sem_post(data->death_spreed.sem);
	}
	return NULL;
}

void	*declare_war(void *arg)
{
	t_data	*data;

	data = arg;
	sem_wait(data->death_spreed.sem);
	int i = 0;
	while (i < data->number_of_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int		i;
	int		status;
	t_philo	*philo;
	pthread_t	tid[2];

	i = -1;
	philos->data->start_time = get_current_time();
	while (++i < philos->data->number_of_philos)
	{
		philos->data->pids[i] = fork();
		if (philos->data->pids[i] == 0)
		{
			start_philo(&(philos[i]));
		}
	}
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
}
