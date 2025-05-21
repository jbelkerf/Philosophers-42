/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/19 13:49:44 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_semaphores(t_philo *philo)
{
	sem_close(philo->data->max_meals.sem);
	sem_close(philo->data->forks.sem);
	sem_close(philo->data->death_spreed.sem);
	sem_close(philo->data->last_meal.sem);
	sem_close(philo->data->meal_num.sem);
	sem_close(philo->data->print.sem);
}

void	free_resources(t_philo *philos)
{
	
	close_semaphores(philos);
	sem_unlink(philos->data->death_spreed.path);
	sem_close(philos->data->last_meal.sem);
	sem_close(philos->data->meal_num.sem);
	sem_unlink(philos->data->forks.path);
	sem_unlink(philos->data->max_meals.path);
	sem_unlink(philos->data->print.path);
	free(philos[0].data->pids);
	free(philos[0].data);
	free(philos);
}
