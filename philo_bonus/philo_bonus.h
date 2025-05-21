/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:44:56 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/19 13:50:13 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	int		number;
	t_mutex	*fork;
}	t_fork;

typedef struct s_flag_sm
{
	sem_t			*sem;
	char			*path;
	long			value;
}	t_flag_sm;



typedef struct s_data
{
	int				number_of_philos;
	int				optional;
	t_flag_sm		print;
	t_flag_sm		forks;
	t_flag_sm		death_spreed;
	t_flag_sm		max_meals;
	t_flag_sm		last_meal;
	t_flag_sm		meal_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	pid_t			*pids;
	void			*philos;
}	t_data;

typedef struct s_philo
{
	int				philo_matricule;
	t_data			*data;
}	t_philo;

//* SIMULATION
void	*start_simulation(t_philo *philos);
void	*routine(void *param);

//* PHILO ACTION
void	take_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
void	give_forks(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	precise_sleep(time_t time_to_wait);
void	ft_think(t_philo *philo);
void	log_routine(t_philo *philo, char *action);

//* ATOI
int		ft_atoi(char *str);

//* INITAILIZE DATA
t_philo	*initialize_philos(t_data *data);
t_data	*initialize_data(int ac, char **av);
int		non_valid_arguments(char **av, int ac);

//* TIME
long	get_timestamp(t_philo *philo);

//* TOOLS
time_t	get_current_time(void);

//* STOP SIMULATION
int		should_stoped(t_philo *philo);
void	*watch_fat_philo_meals(void *arg);
void	*declare_war(void *arg);
void	close_semaphores(t_philo *philo);

//* FREE RESOURCES
void	free_resources(t_philo *philos);

//* MOUNITOR
void	*monitor(void *arg);

//* SETTER GETTER
long	get_sem(t_flag_sm *flag);
void	set_sem(t_flag_sm *flag, long value);
void	increment_sem(t_flag_sm *flag);

//* start
void	unified_start(t_philo *philo);

#endif
