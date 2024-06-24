/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/24 13:27:04 by ewoillar         ###   ########.fr       */
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

typedef struct s_philo
{
	int				philo_id;
	int				philo_max;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				rounds;
	int				isalive;
	int				forks;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct timeval	actual_time;
	struct timeval	start;
	long			time_start;
	long			time_last_meal;
}	t_philo;

typedef struct s_data
{
	int 			alive;
	pthread_mutex_t	*lock;
	t_philo			*philo;
}	t_data;

//utils
void    ft_putstr(int fd, char *str);
void	ft_putchar(int fd, char c);
int		ft_atoi(const char *nptr);
int		ft_check_str(const char *str);
int		ft_isnum(char c);
int		init_threads(t_data *data);
void	printlog(t_philo *philo, char *str, t_data *data);

#endif