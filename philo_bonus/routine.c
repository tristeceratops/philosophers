/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:40:45 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/30 14:01:22 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	sem_wait(&philo->data->sem);
	printlog(philo, philo->data, FORK, 0);
	usleep(100);
	sem_wait(&philo->data->sem);
	printlog(philo, philo->data, FORK, 0);
	printlog(philo, philo->data, EAT, 0);
	philo->tlm = get_current_time();
	philo->nb_meal++;
	ft_usleep(philo->data->time_eat);
	sem_post(&philo->data->sem);
	sem_post(&philo->data->sem);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
	{
		printlog(p, p->data, THINK, 0);
		ft_usleep(p->data->time_eat / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&p->data->check_death);
		if (p->data->dead || p->data->all_ate)
		{
			pthread_mutex_unlock(&p->data->check_death);
			break ;
		}
		pthread_mutex_unlock(&p->data->check_death);
		philo_eat(p);
		sleepy(p);
	}
	return (NULL);
}
