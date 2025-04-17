/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 16:47:04 by jbelkerf         ###   ########.fr       */
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
	data->forks = malloc(data->number_of_philos * sizeof(pthread_mutex_t));
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&(data->forks[i++]), NULL);
	}
	return (data);
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
		i++;
	}
	return (philos);
}
