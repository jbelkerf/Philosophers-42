/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:02 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/17 15:46:52 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"



long	get_sem(t_flag_sm *flag)
{
	long	value;
	sem_wait(flag->sem);
	value = flag->value;
	sem_post(flag->sem);
	return (value);
}

void	set_sem(t_flag_sm *flag, long value)
{
	sem_wait(flag->sem);
	flag->value = value;
	sem_post(flag->sem);
}

void	increment_sem(t_flag_sm *flag)
{
	sem_wait(flag->sem);
	flag->value = flag->value + 1;
	sem_post(flag->sem);
}
