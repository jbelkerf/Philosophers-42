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

t_data	*initialize_data(int ac, char **av)
{
	t_data	data;
	int		i;

	data.number_of_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 7)
		data.optional = ft_atoi(av[5]);
	else
		data.optional = -1;
	pthread_mutex_init(&(data.print), NULL);
	i = 0;
	data.forks = malloc(data.number_of_philos * sizeof(pthread_mutex_t **));
	while (i < data.number_of_philos)
	{
		data.forks[i] = malloc(sizeof(pthread_mutex_t *));
		pthread_mutex_init(data.forks[i++], NULL);
	}
	return (&data);
}

t_philo	**initialize_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo **));
	while (i < data->number_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo *));
		philos[i]->data = data;
		philos[i]->philo_matricule = i;
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

void	routine(void *arg)
{
	t_philo **philo;

	philo = (t_philo *)arg;
}

int	main(int ac, char **av)
{
	t_philo	**philos;
	int		i = 0;

	non_valid_arguments(ac);
	philos = initialize_philos(initialize_data(ac, av));
	
}
