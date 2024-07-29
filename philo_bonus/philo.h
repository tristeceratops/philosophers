/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/29 15:41:55 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/types.h>
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"
# define SEM "/philo"

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	long long			tlm;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_max_eat;
	int					dead;
	int					all_ate;
	int					philo_pid[300];
	long long			start_time;
	pthread_t			check_threads[300];
	sem_t				sem;
	t_philo				philosophers[300];
	pthread_mutex_t		meal_check;
	pthread_mutex_t		check_death;
	pthread_mutex_t		check_write;
}	t_data;

int			ft_atoi(const char *nptr);
int			ft_check_str(const char *str);
int			ft_isnum(char c);
void		printlog(t_philo *philo, t_data *data, char *str, int dead_call);
void		ft_usleep(long long time);
long long	get_current_time(void);
int			ft_thread(t_data *data);
void		ft_exit(t_data *data);
void		printlog(t_philo *philo, t_data *data, char *str, int dead_call);
void		join_thread(t_data *data, t_philo *philos);
void		sleepy(t_philo *philo);
void		ft_exit(t_data *data);
void		is_solo(t_philo *philo);
void		all_ate(t_data *data, t_philo *philos);
void		*routine(void *arg);
void		*routine_last(void *arg);
int			is_parent(t_data *data);
int			waiting_all(t_data *data);

#endif