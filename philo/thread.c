/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/28 15:03:09 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_sleeping(t_philo *philo)
{
	philo->time_last_meal = get_current_time();
	pthread_mutex_lock(&philo->data->eat_mutext);
	printlog(philo, EAT);
	ft_usleep(philo->data->time_eat);
	printlog(philo, SLEEP);
	ft_usleep(philo->data->time_sleep);
	pthread_mutex_unlock(&philo->data->eat_mutext);
}

int	ph_fork(pthread_mutex_t *fork, t_philo *ph)
{
	if (!pthread_mutex_lock(fork))
		printlog(ph, FORK);
	else
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->philo_id % 2 == 0)
		ft_usleep(10 * ph->data->philo_max);
	ph->time_start = get_current_time();
	printf("start id %d\n", ph->philo_id);
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
		if (ph_fork(ph->l_fork, ph) || ph_fork(ph->r_fork, ph))
			printf("error fork mutex\n");
		if (ph->data->alive == 1)
			eating_sleeping(ph);
	}
}

void	*death_routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ft_usleep(ph->data->time_die / 2);
	while (1)
	{
		if (ph->data->alive == 0)
			return (NULL);
		if (get_current_time() - ph->time_last_meal > ph->data->time_die)
		{
			pthread_mutex_lock(&ph->data->finish_mutext);
			ph->data->alive = 0;
			printlog(ph, DEATH);
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
	//detach all threads
	return (0);
}