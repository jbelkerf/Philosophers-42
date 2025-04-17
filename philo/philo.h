/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/17 13:21:25 by jbelkerf         ###   ########.fr       */
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
	pthread_mutex_t	print;
	pthread_mutex_t	**forks;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional;
	pthread_t		*tids;
}	t_data;

typedef struct s_philo{
	t_data	*data;
	int		philo_matricule;
}	t_philo;


// atoi
int		ft_atoi(char *str);


// initial_data
t_philo	*initialize_philos(t_data *data);
t_data	*initialize_data(int ac, char **av);
void	non_valid_arguments(char ac);
void	print_philos(t_philo *philo);

#endif
