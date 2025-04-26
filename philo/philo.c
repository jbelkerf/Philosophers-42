/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 12:38:50 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_philo *philo)
{
	printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
	return (NULL);
}

void	*routine(void *param)
{
	t_philo			*philo;
	struct timeval	time_now;

	philo = param;
	gettimeofday(&time_now, NULL);
	philo->last_meal = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	while (1337)
	{
		take_fork(philo);//  * TAKE FORKs 
		// if (should_stoped(philo))
		// 	return (NULL);
		philo_eat(philo);//				* EAT
		give_forks(philo);//			* GIVE FORKS
		philo_sleep(philo);//	   		* SLEEP
		philo_think(philo);//         	* THINK
	// 	if (should_stoped(philo))
	// 		return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_philo *philos)
{
	int				i;
	pthread_t		*tids;
	struct timeval	time_now;
	time_t			current_time;

	i = -1;
	gettimeofday(&time_now, NULL);
	current_time = (time_now.tv_usec / 1000) + (time_now.tv_sec * 1000);
	philos[0].data->start_time = current_time;
	tids = philos->data->tids;
	while (++i < philos[0].data->number_of_philos)
	{
		if (i % 2 == 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	}
	i = -1;
	while (++i < philos[0].data->number_of_philos)
	{
		if (i % 2 != 0)
			pthread_create(&(tids[i]), NULL, routine, &(philos[i]));
	}
	i = 0;
	while (i < philos[0].data->number_of_philos)
		pthread_join(philos[0].data->tids[i++], NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (non_valid_arguments(av, ac))
		return (1);
	philos = initialize_philos(initialize_data(ac, av));
	start_simulation(philos);
}
