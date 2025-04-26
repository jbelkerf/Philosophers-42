/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:38:10 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 15:46:50 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_philo *philos)
{
	free(philos[0].data->forks);
	free(philos[0].data->tids);
	free(philos[0].data);
	free(philos);
}
