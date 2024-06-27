/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/25 14:08:39 by ewoillar         ###   ########.fr       */
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
	int				isalive;
	pthread_t		thread;
	pthread_t		death_thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			time_start;
	long			time_last_meal;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				rounds;
	int				philo_max;
	int 			alive;
	pthread_mutex_t	start_mutext;
	pthread_mutex_t	eat_mutext;
	pthread_mutex_t	finish_mutext;
	t_philo			**philo;
}	t_data;

typedef struct s_thread
{
	t_philo			*philo;
	t_data			*data;
}	t_thread;

//utils
int		ft_atoi(const char *nptr);
int		ft_check_str(const char *str);
int		ft_isnum(char c);
int		init_threads(t_data *data);
void	printlog(t_philo *philo, char *str);

#endif