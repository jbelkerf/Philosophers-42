/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:39:13 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/16 11:55:58 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>//!to be removed

int	ft_isdigit(char c)
{
	return (c <= '9' && c >= '0');
}

int	ft_strlen(char *str)
{
	int	i;

	while (str[i])
	{
		i++;
	}
	return (i);
}

long	time_atoi(char *str)
{
	unsigned long	ff;

	ff = 0;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > ft_strlen("9223372036854775807"))
		return (-1);
	while (*str >= '0' && *str <= '9')
		ff = ff * 10 + *(str++) - '0';
	if (*str != '\0' || ff > LONG_MAX)
		return (-1);
	return (ff);
}

int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
	{
		i++;
	}
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	non_valid_arguments(char **av, int ac)
{
	int	i;

	i = 2;
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31mUsage Eroor!\n");
		printf("\033[38;5;208mHow to use:\n\tphilo number_of_philosophers");
		printf("\033[38;5;208m time_to_die time_to_eat time_to_sleep [numbe");
		printf("\033[38;5;208mr_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (i < ac)
	{
		if (time_atoi(av[i]) == -1)
		{
			printf("\033[0;31m%s is non valide number\n", av[i]);
			return (1);
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
	{
		return (printf("\033[0;31mnumber of philos is more than 200\n"), 1);
	}
	return (0);
}
