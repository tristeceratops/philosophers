/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/08 15:26:56 by ewoillar         ###   ########.fr       */
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
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEATH "died"
typedef struct s_philo
{
	int					id;
	int					numb_meal;
	int					l_fork_id;
	int					r_fork_id;
	int					forks;
	long long			time_last_meal;
	struct s_data		*data;
	pthread_t			thread;
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
	long long			first_time;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[300];
	pthread_mutex_t		check_death;
	pthread_mutex_t		check_write;
	t_philo				philosophers[300];
}	t_data;

int			ft_atoi(const char *nptr);
int			ft_check_str(const char *str);
int			ft_isnum(char c);
void		printlog(t_philo *philo, t_data *data, char *str, int dead_call);
void		ft_usleep(long long time, t_data *data);
long long	get_current_time(void);
int			ft_thread(t_data *data);
void		ft_putstr(char *s, int fd);
void		ft_putchar(char c, int fd);
void 		ft_exit(t_data *data);
void		ft_putnbr_fd(long long n, int fd);

#endif