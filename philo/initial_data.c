/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 11:57:06 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
	data->forks = malloc(data->number_of_philos * sizeof(t_mutex));
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
	data->philos = philos;
	while (i < data->number_of_philos)
	{
		philos[i].data = data;
		philos[i].philo_matricule = i;
		philos[i].last_meal = 0;
		philos[i].number_of_meals = 0;
		set_forks(&philos[i]);
		i++;
	}
	return (philos);
}

int	ft_isdigit(char c)
{
	return (c <= '9' && c >= '0');
}

int	is_valide_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
	{
		i++;
	}
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	non_valid_arguments(char **av, int ac)
{
	int	i;

	i = 2;
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31mUsage Eroor!\n");
		printf("\033[38;5;208mHow to use:\n\tphilo number_of_philosophers time_");
		printf("\033[38;5;208mto_die time_to_eat time_to_sleep [number_of_");
		printf("\033[38;5;208mtimes_each_philosopher_must_eat]\n");
		return (1);
	}
	while (i < ac)
	{
		if (!is_valide_number(av[i]))
		{
			printf("\033[0;31m%s is non valide number\n", av[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
