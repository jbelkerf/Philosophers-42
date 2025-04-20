/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/20 11:46:13 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*die(t_philo *philo)
{
	printf("%ld %d died\n", get_timestamp(philo), philo->philo_matricule);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	non_valid_arguments(ac);
	philos = initialize_philos(initialize_data(ac, av));
	// return 0;//!to be removed
	start_simulation(philos);
}
