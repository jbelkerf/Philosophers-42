/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:02 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/01 13:45:50 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getter(t_flag *flag)
{
	long	value;

	lock(&(flag->mutex));
	value = flag->value;
	unlock(&(flag->mutex));
	return (value);
}

void	setter(t_flag *flag, long value)
{
	lock(&((*flag).mutex));
	(*flag).value = value;
	unlock(&((*flag).mutex));
}

void	increment_flag(t_flag *flag)
{
	lock(&(flag->mutex));
	flag->value++;
	unlock(&(flag->mutex));
}
