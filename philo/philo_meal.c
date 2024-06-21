/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:07:57 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/21 13:13:27 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_data *data, t_philo *philo)
{
	printlog(philo, "is sleeping", data);
	usleep(data->time_sleep);
}

void	eating(t_data *data, t_philo *philo)
{
	printlog(philo, "is eating", data);
	usleep(data->time_eat);
	sleeping(data, philo);
}

void	thinking(t_data *data, t_philo *philo)
{
	printlog(philo, "is thinking", data);
}

void	forking(t_data *data, t_philo *philo)
{
	philo->forks++;
	printlog(philo, "has taken a fork", data);
}


void	meal(t_data *data, t_philo *philo)
{
	long	time;
	
	time = 0;
	while (philo->isalive && !data->is_dead)
	{
		gettimeofday(&data->actual_time, NULL);
		time = data->actual_time.tv_usec + (data->actual_time.tv_sec * 1000);
		if (philo->last_meal >= 0 && time - philo->last_meal >= data->time_die)
			printlog(philo, "dead lol" , data);
		if (pthread_mutex_lock(philo->l_fork))
			thinking(data, philo);
		else
			forking(data, philo);
		if (pthread_mutex_lock(philo->r_fork))
			thinking(data,philo);
		else
			forking(data, philo);
		if (philo->forks == 2)
		{
			eating(data, philo);
			gettimeofday(&data->actual_time, NULL);
			time = data->actual_time.tv_usec + (data->actual_time.tv_sec * 1000);
			philo->last_meal = time;
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			break ;
		}
	}
}