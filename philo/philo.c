/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 13:49:05 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *param)
{
	t_philo	*philo;

	philo = param;
	printf("philo number %d dkhal\n", philo[0].philo_matricule);
}

void	start_simulation(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 == 0)
			pthread_create(&(philos->data->tids[i]), NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(philos->data->tids[i]), NULL, (void *)routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		pthread_join(philos[0].data->tids[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	non_valid_arguments(ac);
	philos = initialize_philos(initialize_data(ac, av));
	start_simulation(philos);
}
