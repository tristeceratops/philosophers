/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:16:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/25 14:57:51 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		printlog(philo, "has taken a fork");
		philo->forks++;
		pthread_mutex_lock(philo->r_fork);
		printlog(philo, "has taken a fork");
		printlog(philo, "is eating");
		philo->forks++;
	}
	else
		printlog(philo, "is thinking");
	usleep(5000);
	printlog(philo, "is thinking");
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	struct timeval	now;
	int				i;
	
	gettimeofday(&philo->start, NULL);
	while (philo->isalive && philo->data->alive)
	{
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			printlog(philo, "has taken a l fork");
			if (pthread_mutex_lock(philo->r_fork) == 0)
			{
				printlog(philo, "has taken a r fork");
				gettimeofday(&now, NULL);
				philo->last_meal = now;
				printlog(philo, "is eating");
				usleep(philo->time_eat * 1000);
				pthread_mutex_unlock(philo->r_fork);
			}
			pthread_mutex_unlock(philo->l_fork);
			printlog(philo, "is sleeping");
			i = 0;
			while (i < philo->time_sleep)
			{
				usleep(1000);
				gettimeofday(&now, NULL);
				if ((now.tv_sec - philo->last_meal.tv_sec) * 1000 + (now.tv_usec - philo->last_meal.tv_usec) / 1000 > philo->time_die)
				{
					printlog(philo, "has died");
					philo->isalive = 0;
					philo->data->alive = 0;
					break ;
				}
			}
		}
		else
			printlog(philo, "is thinking");
		gettimeofday(&now, NULL);
		if ((now.tv_sec - philo->last_meal.tv_sec) * 1000 + (now.tv_usec - philo->last_meal.tv_usec) / 1000 > philo->time_die)
		{
			printlog(philo, "has died");
			philo->isalive = 0;
			philo->data->alive = 0;
		}
	}

	return NULL;
}

void	*philo_thread(void *arg)
{
	t_philo *philo;
	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->data->start_mutext);
	philo->data->start_counter++;
	while (philo->data->start_counter < philo->data->philo_max)
	{
		pthread_mutex_unlock(&philo->data->start_mutext);
		usleep(100);
		pthread_mutex_lock(&philo->data->start_mutext);
	}
	pthread_mutex_unlock(&philo->data->start_mutext);
	philo_routine(philo);
	return (philo);
}

int	init_threads(t_data *data)
{
	int i;
	i = 0;
	while (i < data->philo_max)
	{
		if (pthread_create(&data->philo[i]->thread , NULL, philo_thread, data->philo[i]))
		{
			printf("error thread\n");
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data->philo_max)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	return (1);
}
