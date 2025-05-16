/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:36:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/16 11:51:23 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unified_start(t_philo *philo)
{
	while (get_current_time() < philo->data->start_time)
	{
		usleep(10);
	}
}

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

	//printf("%d dkhal\n", philo->philo_matricule);
	unified_start(philo);
	pthread_create(&tid, NULL, monitor, philo);
	routine(philo);
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
	sem_wait(data->print.sem);
	usleep(10);
	sem_post(data->death_spreed.sem);
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
	philos->data->start_time = get_current_time() + 1000;  //*set start time
	while (++i < philos->data->number_of_philos)//
	{
		if (i % 2 == 0)
		{
			philos->data->pids[i] = fork();          //   
			if (philos->data->pids[i] == 0)          //
			{                                        //*launch philos**
				start_philo(&(philos[i]));           //
			}                                        //
		}                                        //
	}  										 //
	//printf("i = %d\n", i);
	i = -1;                                        
	while (++i < philos->data->number_of_philos)//
	{   
		if (i % 2 != 0)
		{
			philos->data->pids[i] = fork();          //   
			if (philos->data->pids[i] == 0)          //
			{                                        //*launch philos**
				start_philo(&(philos[i]));           //
			}                                        //
		}                                        //
	}                                           //
	//printf("i = %d\n", i);
	if (philos->data->optional != -1)                                        ///
		pthread_create(&(tid[0]), NULL, watch_fat_philo_meals, philos->data); ///*checck for max meals
	pthread_create(&(tid[1]), NULL, declare_war, philos->data);  //**hoock for died or max meals */
	if (philos->data->optional != -1)
		pthread_join(tid[0], NULL);///*join
	pthread_join(tid[1], NULL);
	i = 0;
	//*sleep(5);//!ms7 ms7
	while (i < philos->data->number_of_philos)
	{
		waitpid(philos->data->pids[i], NULL, 0);//*wait
		i++;
	}
}
