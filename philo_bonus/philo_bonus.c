/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/18 13:05:05 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unified_start(t_philo *philo)
{
	while (get_current_time() < philo->data->start_time)
	{
		usleep(5);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (non_valid_arguments(av, ac))
		return (1);
	philos = initialize_philos(initialize_data(ac, av));
	if (!philos)
		return (1);
	start_simulation(philos);
	free_resources(philos);
}
