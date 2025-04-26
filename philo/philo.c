/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:22:08 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 16:08:02 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int ac, char **av)
{
	t_philo	*philos;

	if (non_valid_arguments(av, ac))
		return (1);
	philos = initialize_philos(initialize_data(ac, av));
	if (!philos)
		return (NULL);
	start_simulation(philos);
	free_resources(philos);
}
