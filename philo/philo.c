/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 15:29:10 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_philo *philo)
{
	printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int				i;
	pthread_t		*tids;
	struct timeval	time_now;

	i = 0;
	gettimeofday(&time_now, NULL);
	philos[0].data->start_time = (time_now.tv_usec / 1000) + (time_now.tv_sec * 1000);
	tids = philos->data->tids;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 == 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
		i++;
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
	{
		pthread_join(philos[0].data->tids[i], NULL);
		i++;
	}
}

void	*routine(void *param)
{
	t_philo			*philo;
	t_mutex			f_fork;
	t_mutex			s_fork;
	struct timeval	time_now;

	philo = param;
	set_forks(&f_fork, &s_fork, philo);
	gettimeofday(&time_now, NULL);
	philo->last_meal = time_now.tv_usec;
	while (1337)
	{
		take_fork(&f_fork, philo);//  * TAKE FIRST  FORK
		take_fork(&s_fork, philo);//  * TAKE SECOND FORK
		philo_eat(philo);//  			       * EAT
		give_fork(&f_fork);//         * GIVE FIRST  FORK
		give_fork(&s_fork);//         * GIVE SECOND FORK
		philo_sleep(philo);//                  * SLEEP
		if (check_die(philo))
			return (die(philo));
		philo_think(philo);//                  * THINK
		if (check_die(philo))
			return (die(philo));
	}
}


int	main(int ac, char **av)
{
	t_philo	*philos;

	non_valid_arguments(ac);
	philos = initialize_philos(initialize_data(ac, av));
	start_simulation(philos);
}
