/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 16:48:07 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*open_the_sem(char *path, int oflag, int mode, int value, t_flag_sm *flag)
{
	sem_t	*sm;
	sem_unlink(path);
	sm = sem_open(path, oflag, mode, value);
	if (sm == SEM_FAILED)
	{
		printf("the sem %s failed to open\n", path);
		exit(1);
	}
	flag->path = path;
	return (sm);
}

t_data	*set_input(t_data	*data, int ac, char **av)
{
	data->death_spreed.sem = open_the_sem("/death", O_CREAT, 0666, 1, &(data->death_spreed));
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
	data->print.sem = open_the_sem("/print", O_CREAT, 0666, 1, &(data->print));
	i = 0;
	data->pids = malloc(data->number_of_philos * sizeof(pid_t));
	if (!data->pids)
		return (NULL);
	data->forks.sem = open_the_sem("/forks", O_CREAT, 0666, data->number_of_philos, &(data->forks));
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
