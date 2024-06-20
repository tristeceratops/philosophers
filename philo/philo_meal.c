/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:07:57 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/20 15:24:24 by ewoillar         ###   ########.fr       */
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
	printlog(philo, "has taken a fork", data);
}

void	meal(t_data *data, t_philo *philo)
{
	int	forks;

	forks = 0;
	if (philo->philo_id % 2)
	{
		if(!pthread_mutex_lock(philo->l_fork))
			forks++;
		else
			thinking(data, philo);
	}
	else if (!(philo->philo_id % 2))
	{
		if(!pthread_mutex_lock(philo->r_fork))
			forks++;
		else
			thinking(data, philo);
		if(!pthread_mutex_lock(philo->l_fork))
		{
			forks++;
		}
		else
		{
			thinking(data, philo);
			usleep(10);
		}
		if(!pthread_mutex_lock(philo->r_fork))
		{
			forks++;
		}
		else
		{
			thinking(data, philo);
			usleep(10);
		}
		if (forks == 2)
			eating(data, philo);
	}
}