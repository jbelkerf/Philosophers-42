/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/14 12:14:36 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  //pthread_create pthread_detach  pthread_join 
//      pthread_mutex_init pthread_mutex_destroy, pthread_mutex_lock,
//               pthread_mutex_unlock
# include <stdio.h>    //printf
# include <string.h>   //memset 
# include <stdlib.h>   //malloc
# include <unistd.h>   //write  usleep 
# include <sys/time.h> //gettimeofday

typedef struct s_data{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	optional;
	pthread_t	*tids;
}	t_data;

int	ft_atoi(char *str);

#endif