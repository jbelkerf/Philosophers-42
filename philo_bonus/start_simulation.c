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
	if (get_sem_value(&(philo->data->death_spreed)))
		return ;
	sem_wait(philo->data->print.sem);
	printf("%ld %d %s\n", get_timestamp(philo), philo->philo_matricule, action);
	sem_post(philo->data->print.sem);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	//printf("routine philo num\n");
	increment_flag(&(philo->started));
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
	int			dead_philo;

	pthread_create(&tid, NULL, routine, philo);
	dead_philo = monitor(philo);
	pthread_join(tid, NULL);
	exit(dead_philo);
}

void	start_simulation(t_philo *philos)
{
	int		i;
	int		status;
	int		pid;

	i = -1;
	philos->data->start_time = get_current_time();
	while (++i < philos->data->number_of_philos)
	{
		//printf(" i = %d \n", i);
		philos->data->pids[i] = fork();
		if (philos->data->pids[i] == 0)
		{
			start_philo(&(philos[i]));
		}
	}
	i = -1;
	pid = waitpid(-1, &status, 0);
	status = WEXITSTATUS(status);
	// printf("the died is %d\n", status);
	printf("%ld %d died\n", get_timestamp(&(philos[status])), philos[status].philo_matricule);
	while (++i < philos[0].data->number_of_philos)
	{
		if (philos->data->pids[i] != pid)
		{
			kill(philos->data->pids[i], SIGKILL);
		}
	}
}
