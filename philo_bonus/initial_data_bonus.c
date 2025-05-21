/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:17:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:56 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*open_t_sem(char *path, int value, t_flag_sm *flag)
{
	sem_t	*sm;

	sem_unlink(path);
	sm = sem_open(path, O_CREAT, 0666, value);
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
	int		num;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data = set_input(data, ac, av);
	num = data->number_of_philos;
	data->print.sem = open_t_sem("/print", 1, &(data->print));
	data->forks.sem = open_t_sem("/forks", num, &(data->forks));
	data->max_meals.sem = open_t_sem("/max_meals", 0, &(data->max_meals));
	data->death_spreed.sem = open_t_sem("/death", 0, &(data->death_spreed));
	data->last_meal.sem = open_t_sem("/last_meal", 1, &(data->last_meal));
	data->meal_num.sem = open_t_sem("/meal_num", 1, &(data->meal_num));
	data->last_meal.value = 9223372036854775806;
	data->pids = malloc(data->number_of_philos * sizeof(pid_t));
	if (!data->pids)
		return (NULL);
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
		i++;
	}
	return (philos);
}
