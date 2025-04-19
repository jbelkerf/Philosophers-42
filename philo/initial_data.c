/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 20:45:30 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->number_of_philos)
	{
		printf("\n\n---> %d\n", philo[i].philo_matricule);
		printf("Time to die: %d\n", philo[i].data->time_to_die);
		printf("Time to eat: %d\n", philo[i].data->time_to_eat);
		printf("Time to sleep: %d\n", philo[i].data->time_to_sleep);
		printf("Optional: %d\n", philo[i].data->optional);
		i++;
	}
}

t_data	*initialize_data(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	data->death_spreed.value = 0;
	data->start_time = 0;
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->optional = ft_atoi(av[5]);
	else
		data->optional = -1;
	pthread_mutex_init(&(data->print), NULL);
	i = 0;
	data->tids = malloc(data->number_of_philos * sizeof(pthread_t));
	pthread_mutex_init(&(data->death_spreed.mutex), NULL);
	data->forks = malloc(data->number_of_philos * sizeof(t_fork));
	while (i < data->number_of_philos)
	{
		data->forks[i].number = i;
		pthread_mutex_init(&(data->forks[i].fork), NULL);
		i++;
	}
	return (data);
}

t_philo	*initialize_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(data->number_of_philos * sizeof(t_philo));
	while (i < data->number_of_philos)
	{
		philos[i].data = data;
		philos[i].philo_matricule = i;
		philos[i].last_meal = 0;
		philos[i].number_of_meals = 0;
		set_forks(&philos[i]); //! here the segvault
		i++;
	}
	return (philos);
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
