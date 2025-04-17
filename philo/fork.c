/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 16:48:15 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo(int philo_matricule, pthread_mutex_t *print_mutex)
{
	pthread_mutex_lock(print_mutex);
	printf("\nphilo %d dkhal\n", philo_matricule);
	pthread_mutex_unlock(print_mutex);
}

void	set_forks(pthread_mutex_t *f, pthread_mutex_t *s, t_philo *philo)
{
	int	philo_num;

	philo_num = philo->philo_matricule;
	//* set the first  fork
	*f = philo->data->forks[philo_num];
	//* set the second fork
	if (philo_num == philo->data->number_of_philos - 1)
		*s = philo->data->forks[0];
	else
		*s = philo->data->forks[philo_num + 1];
}

void	take_fork(pthread_mutex_t *f_fork, pthread_mutex_t *s_fork, t_philo *philo)
{
	pthread_mutex_lock(f_fork);
	pthread_mutex_lock(s_fork);
	printf("TIME %d has taken a fork\n", philo->philo_matricule);
}

void	give_fork(pthread_mutex_t *f_fork, pthread_mutex_t *s_fork)
{
	pthread_mutex_unlock(f_fork);
	pthread_mutex_unlock(s_fork);
}

void	philo_eat(t_philo *philo)
{
	usleep(philo->data->time_to_eat * 1000);
	printf("TIME %d is eating\n", philo->philo_matricule);
}

void	philo_sleep(t_philo *philo)
{
	printf("TIME %d is sleeping\n", philo->philo_matricule);
	usleep(philo->data->time_to_sleep * 1000);
}
void	philo_think(t_philo *philo)
{
	printf("TIME %d is thinking\n", philo->philo_matricule);
}
