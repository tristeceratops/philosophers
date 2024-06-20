/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/20 15:21:26 by ewoillar         ###   ########.fr       */
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
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_data
{
	int				philo_max;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				rounds;
	int				is_dead;
	struct timeval	start;
	t_philo			*head;
}	t_data;

//utils
void    ft_putstr(int fd, char *str);
void	ft_putchar(int fd, char c);
int		ft_atoi(const char *nptr);
int		ft_check_str(const char *str);
int		ft_isnum(char c);
int		init_threads(t_data *data, t_philo *philo);
void	printlog(t_philo *philo, char *str, t_data *data);
void	meal(t_data *data, t_philo *philo);

#endif