/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:32:21 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/17 18:04:33 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepy(t_philo *philo)
{
	printlog(philo, philo->data, SLEEP, 0);
	ft_usleep(philo->data->time_sleep);
	printlog(philo, philo->data, THINK, 0);
}

void	is_solo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->tlm = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_death);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
}

void	all_ate(t_data *data, t_philo *philos)
{
	int		nb_meal;
	int		i;

	i = 0;
	pthread_mutex_lock(&data->meal_check);
	nb_meal = philos[i].nb_meal;
	pthread_mutex_unlock(&data->meal_check);
	while (data->nb_max_eat != -1 && i < data->nb_philo \
			&& nb_meal >= data->nb_max_eat)
		{
			i++;
			pthread_mutex_lock(&data->meal_check);
			nb_meal = philos[i].nb_meal;
			pthread_mutex_unlock(&data->meal_check);
		}
		pthread_mutex_lock(&data->check_death);
		if (i == data->nb_philo)
			data->all_ate = 1;
		pthread_mutex_unlock(&data->check_death);
}

void	printlog(t_philo *philo, t_data *data, char *str, int dead_call)
{
	struct timeval	t;
	long long		t_tamp;
	int				dead;

	pthread_mutex_lock(&data->check_write);
	pthread_mutex_lock(&data->check_death);
	dead = data->dead;
	pthread_mutex_unlock(&data->check_death);
	if (!dead || dead_call)
	{
		gettimeofday(&t, NULL);
		t_tamp = (t.tv_sec * 1000) + (t.tv_usec / 1000) - data->first_time;
		printf("%lld %d %s\n", t_tamp, philo->id, str);
	}
	pthread_mutex_unlock(&data->check_write);
}
