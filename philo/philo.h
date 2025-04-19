/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 12:50:37 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // *pthread_create pthread_detach  pthread_join 
// *     pthread_mutex_init pthread_mutex_destroy, pthread_mutex_lock,
//*               pthread_mutex_unlock
# include <stdio.h>    //*printf
# include <string.h>   //*memset 
# include <stdlib.h>   //*malloc
# include <unistd.h>   //*write  usleep 
# include <sys/time.h> //*gettimeofday

typedef struct s_flag{
	pthread_mutex_t	mutex;
	int				value;
}	t_flag;

typedef struct s_data{
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	int				number_of_philos;
	t_flag			dead_spreed;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional;
	long			start_time;
	pthread_t		*tids;
}	t_data;

typedef struct s_philo{
	t_data	*data;
	long	last_meal;
	int		number_of_meals;
	int		philo_matricule;
}	t_philo;

typedef pthread_mutex_t	t_mutex;

//* ATOI
int		ft_atoi(char *str);


//* INITAILIZE DATA
t_philo	*initialize_philos(t_data *data);
t_data	*initialize_data(int ac, char **av);
void	non_valid_arguments(char ac);
void	print_philos(t_philo *philo);

//* LOG PHILO
void	log_philo(int philo_matricule, pthread_mutex_t *print_mutex);

//* FORKS
void	set_forks(pthread_mutex_t *f, pthread_mutex_t *s, t_philo *philo);
void	take_fork(pthread_mutex_t *f_fork, pthread_mutex_t *s_fork, t_philo *philo);
void	give_fork(pthread_mutex_t *f_fork, pthread_mutex_t *s_fork);

//* THINK
void	philo_think(t_philo *philo);

//* SLEEP
void	philo_sleep(t_philo *philo);

//* EAT
void	philo_eat(t_philo *philo);

//* DIE
int		check_die(t_philo *philo);

//* TIME
long	get_timestamp(t_philo *philo);

#endif
