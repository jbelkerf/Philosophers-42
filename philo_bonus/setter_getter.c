/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:02 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 18:04:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getter(t_flag_mu *flag)
{
	long	value;

	lock(&(flag->mutex));
	value = flag->value;
	unlock(&(flag->mutex));
	return (value);
}

void	setter(t_flag_mu *flag, long value)
{
	lock(&((*flag).mutex));
	(*flag).value = value;
	unlock(&((*flag).mutex));
}

void	increment_flag(t_flag_mu *flag)
{
	lock(&(flag->mutex));
	flag->value++;
	unlock(&(flag->mutex));
}

long	get_sem_value(t_flag_sm *flag)
{
	long	value;

	sem_wait(flag->sem);
	value = flag->value;
	sem_post(flag->sem);
	return (value);
}

void	set_sem_value(t_flag_sm *flag, long value)
{
	sem_wait(flag->sem);
	flag->value = value;
	sem_post(flag->sem);
}
