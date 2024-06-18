/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:41 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/18 16:13:33 by ewoillar         ###   ########.fr       */
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
	int	philo_id;
	int	isalive;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

typedef struct s_data
{
	int	philo_max;
	int	time_die;
	int	time_eat;
	int time_sleep;
	int	rounds;
	int	is_dead;
	struct timeval start;
	pthread_t	*thread;
}	t_data;

//utils
void    ft_putstr(int fd, char *str);
void	ft_putchar(int fd, char c);
int		ft_atoi(const char *nptr);
int		ft_check_str(const char *str);
int		ft_isnum(char c);

#endif