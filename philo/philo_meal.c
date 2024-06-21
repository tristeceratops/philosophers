/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:07:57 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/21 11:23:58 by ewoillar         ###   ########.fr       */
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
	printf("debut de repas pour philo n %d\n", philo->philo_id);
	while (philo->isalive && !data->is_dead)
	{
		forking(data, philo);
		forks++;
		if (forks)
			break ;
	}
	pthread_exit(0);
}