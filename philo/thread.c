/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/28 11:33:34 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (ph->data->alive == 0)
			return (NULL);
		pthread_mutex_lock(&ph->data->start_mutext);
		if (ph->data->alive == 0)
		{
			pthread_mutex_unlock(&ph->data->start_mutext);
			return (NULL);
		}
		if (ph->data->alive == 1)
		{
			ph->time_last_meal = get_current_time();
			printlog(ph, "is eating");
			pthread_mutex_unlock(&ph->data->start_mutext);
			ft_usleep(ph->data->time_eat * 1000);
			pthread_mutex_lock(&ph->data->eat_mutext);
			ph->data->rounds++;
			pthread_mutex_unlock(&ph->data->eat_mutext);
			printlog(ph, "is sleeping");
			ft_usleep(ph->data->time_sleep * 1000);
			printlog(ph, "is thinking");
		}
	}
}

void	*death_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (ph->data->alive == 0)
			return (NULL);
		if (get_current_time() - ph->time_last_meal > ph->data->time_die)
		{
			pthread_mutex_lock(&ph->data->finish_mutext);
			ph->data->alive = 0;
			printlog(ph, "died");
			pthread_mutex_unlock(&ph->data->finish_mutext);
			return (NULL);
		}
	}
	return (NULL);
}

int	thread(t_thread *thread)
{
	int i;

	i = 0;
	while (i < thread->data->philo_max)
	{
		if (pthread_create(&thread->data->philo[i].thread, NULL, &routine, &thread->data->philo[i]))
			return (1);
		if (pthread_create(&thread->data->philo[i].death_thread, NULL, &death_routine, &thread->data->philo[i]))
			return (1);
		i++;
	}
	return (0);
}