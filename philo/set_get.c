/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:14:02 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/30 21:41:07 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	geter(t_flag *flag)
{
	long	value;

	lock(&(*flag).mutex);
	value = (*flag).value;
	unlock(&((*flag).mutex));
	return (value);
}

void	seter(t_flag *flag, int value)
{
	lock(&((*flag).mutex));
	(*flag).value = value;
	unlock(&((*flag).mutex));
}
