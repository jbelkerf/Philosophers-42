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

void	initialite_data(int ac, char **av, t_data *data)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->optional = -1;
	data->tids = malloc(sizeof(pthread_t) * (data->number_of_philos));
	if (ac == 6)
		data->optional = ft_atoi(av[5]);
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
	t_data	*data;

	data = (t_data *)arg;
	printf("\n----hey i am philosopher");
	printf("Thread %d started----\n", (int)pthread_self());
	pthread_exit(NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	int			i = 0;

	non_valid_arguments(ac);
	initialite_data(ac, av, &data);
	//print_data(&data);
	while (i < data.number_of_philos)
	{
		pthread_create(&data.tids[i], NULL, (void *)routine, (void *)&data);
		i++;
	}
}
