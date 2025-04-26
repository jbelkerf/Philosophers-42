/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/26 13:43:58 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_timestamp(t_philo *philo)
{
	return (get_current_time() - philo->data->start_time);
}

void	set_forks(t_philo *philo)
{
	int	philo_num;

	philo_num = philo->philo_matricule;
	philo->first_fork.fork = &(philo->data->forks[philo_num]);
	philo->first_fork.number = philo_num;
	if (philo_num == philo->data->number_of_philos - 1)
	{
		philo->second_fork.fork = &(philo->data->forks[0]);
		philo->second_fork.number = 0;
	}
	else
	{
		philo->second_fork.fork = &(philo->data->forks[philo_num + 1]);
		philo->second_fork.number = philo_num + 1;
	}
}

void	precise_sleep(time_t time_to_wait)
{
	time_t			start;
	time_t			current;

	current = get_current_time();
	start = current;
	while (current < start + time_to_wait)
	{
		usleep(100);
		current = get_current_time();
	}
}

time_t	get_current_time(void)
{
	struct timeval	time_now;
	time_t			result;

	gettimeofday(&time_now, NULL);
	result = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return (result);
}

int	ft_atoi(char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
		if (n < 0 && sign == -1)
			return (0);
		else if (n < 0 && sign == 1)
			return (-1);
	}
	return ((int)(sign * n));
}
