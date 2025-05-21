/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:41 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/21 13:12:08 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*watch_fat_philo_meals(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = arg;
	while (i < data->number_of_philos)
	{
		sem_wait(data->max_meals.sem);
		i++;
	}
	i = 0;
	sem_post(data->death_spreed.sem);
	return (NULL);
}

void	*declare_war(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	sem_wait(data->death_spreed.sem);
	i = 0;
	while (i < data->number_of_philos)
	{
		sem_post(data->max_meals.sem);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	return (NULL);
}
