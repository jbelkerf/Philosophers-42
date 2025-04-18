/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/04/19 17:39:19 by jbelkerf         ###   ########.fr       */
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
	long			value;
}	t_flag;

typedef struct s_data{
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	int				number_of_philos;
	t_flag			death_spreed;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				optional;
	time_t			start_time;
	pthread_t		*tids;
}	t_data;

typedef struct s_philo{
	t_data			*data;
	pthread_mutex_t *first_fork;
	pthread_mutex_t	*second_fork;
	long			last_meal;
	int				number_of_meals;
	int				philo_matricule;
}	t_philo;

typedef pthread_mutex_t	t_mutex;


//* SIMULATION
void	start_simulation(t_philo *philos);
void	*routine(void *param);


//* PHILO ACTION
void	take_fork(t_mutex *fork, t_philo *philo);
void	philo_eat(t_philo *philo);
void	give_forks(t_mutex *first_fork, t_mutex *second_fork);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*die(t_philo *philo);

//* ATOI
int		ft_atoi(char *str);


//* INITAILIZE DATA
t_philo	*initialize_philos(t_data *data);
t_data	*initialize_data(int ac, char **av);
void	non_valid_arguments(char ac);
void	print_philos(t_philo *philo);


//* FORKS
void	set_forks(t_mutex *f, t_mutex *s, t_philo *philo);

//* DIE
int		check_die(t_philo *philo);

//* TIME
long	get_timestamp(t_philo *philo);

#endif
