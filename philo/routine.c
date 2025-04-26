/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 15:24:09 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	matricule;

	if (should_stoped(philo))
		return ;
	matricule = philo->philo_matricule;
	if (matricule % 2 == 0)
	{
		pthread_mutex_lock(philo->first_fork.fork);
		log_routine(philo, "has taken a fork");
		pthread_mutex_lock(philo->second_fork.fork);
		log_routine(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->second_fork.fork);
		log_routine(philo, "has taken a fork");
		pthread_mutex_lock(philo->first_fork.fork);
		log_routine(philo, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	if (should_stoped(philo))
		return ;
	log_routine(philo, "is eating");
	philo->last_meal = get_current_time();
	precise_sleep(philo->data->time_to_eat);
	philo->number_of_meals++;
}

void	ft_sleep(t_philo *philo)
{
	if (should_stoped(philo))
		return ;
	log_routine(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	if (should_stoped(philo))
		return ;
	log_routine(philo, "is thinking");
}

void	give_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork.fork);
	pthread_mutex_unlock(philo->second_fork.fork);
}
