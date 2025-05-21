/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:04:30 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/17 15:46:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks.sem);
	log_routine(philo, "has taken a fork");
	sem_wait(philo->data->forks.sem);
	log_routine(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	log_routine(philo, "is eating");
	if (get_sem(&(philo->meal_num)) == philo->data->optional)
		sem_post(philo->data->max_meals.sem);
	set_sem(&(philo->last_meal), get_current_time());
	precise_sleep(philo->data->time_to_eat);
	increment_sem(&(philo->meal_num));
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
