/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 16:48:35 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo			*philo;
	pthread_mutex_t	f_fork;
	pthread_mutex_t	s_fork;

	philo = param;
	set_forks(&f_fork, &s_fork, philo);
	while (1337)
	{
		log_philo(philo->philo_matricule, &(philo->data->print));
		take_fork(&f_fork, &s_fork, philo);//  * TAKE a FORK
		philo_eat(philo);//  			* EAT
		give_fork(&f_fork, &s_fork);//  * GIVE a FORK
		philo_sleep(philo);//           * SLEEP
		philo_think(philo);//           * THINK
	}
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 == 0)
			pthread_create(&(philos->data->tids[i]), NULL, routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(philos->data->tids[i]), NULL, routine, &(philos[i]));
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
