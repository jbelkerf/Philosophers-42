/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 21:02:16 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo			*philo;
	pthread_mutex_t	f_fork;
	pthread_mutex_t	s_fork;
	struct timeval	time_now;

	philo = param;
	set_forks(&f_fork, &s_fork, philo);
	log_philo(philo->philo_matricule, &(philo->data->print));
	gettimeofday(&time_now, NULL);
	philo->last_meal = time_now.tv_usec;
	philo->data->start_time = time_now.tv_usec;
	while (1337)
	{
		take_fork(&f_fork, &s_fork, philo);//  * TAKE a FORK
		if (check_die(philo))
		{
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
			return (NULL);
		}
		philo_eat(philo);//  			       * EAT
		give_fork(&f_fork, &s_fork);//         * GIVE a FORK
		if (check_die(philo))
		{
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
			return (NULL);
		}
		philo_sleep(philo);//                  * SLEEP
		if (check_die(philo))
		{
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
			return (NULL);
		}
		philo_think(philo);//                  * THINK
		if (check_die(philo))
		{
			printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
			return (NULL);
		}
	}
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
