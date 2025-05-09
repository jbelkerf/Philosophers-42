/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/09 16:40:08 by jbelkerf         ###   ########.fr       */
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
#include <semaphore.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork{
	int		number;
	t_mutex	*fork;
}	t_fork;

typedef struct s_flag_sm{
	sem_t			*sem;
	long			value;
	char			*path;
}	t_flag_sm;

typedef struct s_flag_mu{
	t_mutex			*mutex;
	long			value;
}	t_flag_mu;

typedef struct s_data{
	t_flag_sm		print;
	t_flag_sm		forks;
	int				number_of_philos;
	t_flag_sm		death_spreed;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				optional;
	time_t			start_time;
	pid_t			*pids;
	void			*philos;
}	t_data;

typedef struct s_philo{
	t_data			*data;
	t_flag_mu		last_meal;
	t_flag_mu		number_of_meals;
	int				philo_matricule;
}	t_philo;

//* SIMULATION
void	start_simulation(t_philo *philos);
void	*routine(t_philo *philo);

//* PHILO ACTION
void	take_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
void	give_forks(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	precise_sleep(time_t time_to_wait);
void	ft_think(t_philo *philo);
void	die(t_philo *philo);
void	log_routine(t_philo *philo, char *action);

//* ATOI
int		ft_atoi(char *str);

//* INITAILIZE DATA
t_philo	*initialize_philos(t_data *data);
t_data	*initialize_data(int ac, char **av);
int		non_valid_arguments(char **av, int ac);

//* FORKS
void	set_forks(t_philo *philo);

//* TIME
long	get_timestamp(t_philo *philo);

//* TOOLS
time_t	get_current_time(void);
int		max_meals(t_philo *philos);

//* STOP SIMULATION
int		should_stoped(t_philo *philo);

//* FREE RESOURCES
void	free_resources(t_philo *philos);

//* MOUNITOR
void	*monitor(void *arg);

//* MUTEX HANDING
void	lock(t_mutex *mutex);
void	unlock(t_mutex *mutex);

//* SETTER GETTER
long	getter(t_flag_mu *flag);
void	setter(t_flag_mu *flag, long value);
void	increment_flag(t_flag_mu *flag);

#endif
