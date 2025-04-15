/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/14 12:35:18 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data *data)
{
	printf("number_of_philos: %d\n", data->number_of_philos);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	if (data->optional != -1)
		printf("optional: %d\n", data->optional);
}

t_philo	*initialite_data(int ac, char **av, t_data *data, t_philo *philo)
{
	int i = 0;

	philo = malloc(data->number_of_philos * sizeof(t_philo));
	data->forks = malloc(data->number_of_philos * sizeof(int));
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->print), NULL);
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->optional = -1;
	data->tids = malloc(sizeof(pthread_t) * (data->number_of_philos));
	if (ac == 6)
		data->optional = ft_atoi(av[5]);
	return (philo);
}

void	non_valid_arguments(char ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31mUsage Eroor!\n");
		printf("\033[38;5;208mHow to use:\n\tphilo number_of_philosophers time_");
		printf("\033[38;5;208mto_die time_to_eat time_to_sleep [number_of_");
		printf("\033[38;5;208mtimes_each_philosopher_must_eat]\n");
		exit(1);
	}
}

void	routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->philo_matricule == philo->data->number_of_philos)
	{
		pthread_mutex_lock(&(philo->data->forks[0]));
	}
	else
		pthread_mutex_lock(&(philo->data->forks[philo->philo_matricule]));
	if (philo->philo_matricule == 1)
		pthread_mutex_lock(&(philo->data->forks[philo->data->number_of_philos - 1]));
	else
		pthread_mutex_lock(&(philo->data->forks[philo->philo_matricule - 1]));
	pthread_mutex_lock(&(philo->data->print));
	printf("----hey i am philosopher %d-----\n", philo->philo_matricule);
	pthread_mutex_unlock(&(philo->data->print));
	usleep(1000000);
	if (philo->philo_matricule == philo->data->number_of_philos)
		pthread_mutex_unlock(&(philo->data->forks[0]));
	else
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_matricule]));
	if (philo->philo_matricule == 1)
		pthread_mutex_unlock(&(philo->data->forks[philo->data->number_of_philos - 1]));
	else
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_matricule - 1]));
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	int		i = 0;

	non_valid_arguments(ac);
	philos = NULL;
	philos = initialite_data(ac, av, philos);
	//print_data(&data);
	while (i < philos.data->number_of_philos)
	{
		if ( i % 2 == 0)
		{
			philos[i].data = &data;
			philos[i].philo_matricule = i + 1;
			pthread_create(&data.tids[i], NULL, (void *)routine, (void *)&(philos[i]));
			i++;
		}
	}
	i = 0;
	while (i < data.number_of_philos)
	{
		if ( i % 2 != 0)
		{
			philos[i].data = &data;
			philos[i].philo_matricule = i + 1;
			pthread_create(&data.tids[i], NULL, (void *)routine, (void *)&(philos[i]));
			i++;
		}
	}
	i = 0;
	while (i < data.number_of_philos)
	{
		pthread_join(data.tids[i], NULL);
		i++;
	}
}
