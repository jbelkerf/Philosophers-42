/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/01 14:34:22 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*set_input(t_data	*data, int ac, char **av)
{
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
	return (data);
}

t_data	*initialize_data(int ac, char **av)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data = set_input(data, ac, av);
	pthread_mutex_init(&(data->print), NULL);
	i = 0;
	data->tids = malloc(data->number_of_philos * sizeof(pthread_t));
	if (!data->tids)
		return (NULL);
	pthread_mutex_init(&(data->death_spreed.mutex), NULL);
	data->forks = malloc(data->number_of_philos * sizeof(t_mutex));
	if (!data->forks)
		return (NULL);
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
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
	if (!philos)
		return (NULL);
	data->philos = philos;
	while (i < data->number_of_philos)
	{
		philos[i].data = data;
		philos[i].philo_matricule = i;
		philos[i].last_meal.value = 0;
		pthread_mutex_init(&(philos[i].last_meal.mutex), NULL);
		pthread_mutex_init(&(philos[i].number_of_meals.mutex), NULL);
		philos[i].number_of_meals.value = 0;
		set_forks(&philos[i]);
		i++;
	}
	return (philos);
}
