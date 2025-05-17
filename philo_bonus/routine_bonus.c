/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/16 12:09:54 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	matricule;

	matricule = philo->philo_matricule;
	sem_wait(philo->data->forks.sem);
	log_routine(philo, "has taken a fork");
	sem_wait(philo->data->forks.sem);
	log_routine(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	log_routine(philo, "is eating");
	if (getter(&(philo->number_of_meals)) == philo->data->optional)
		sem_post(philo->data->max_meals.sem);
	setter(&(philo->last_meal), get_current_time());
	precise_sleep(philo->data->time_to_eat);
	increment_flag(&(philo->number_of_meals));
}

void	ft_sleep(t_philo *philo)
{
	log_routine(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	log_routine(philo, "is thinking");
}

void	give_forks(t_philo *philo)
{
	sem_post(philo->data->forks.sem);
	sem_post(philo->data->forks.sem);
}
