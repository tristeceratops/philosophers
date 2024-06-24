/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:16:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/24 11:33:35 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		printlog(philo, "has taken a fork", philo->data);
		philo->forks++;
		pthread_mutex_lock(philo->r_fork);
		printlog(philo, "has taken a fork", philo->data);
		philo->forks++;
	}
	else
		printlog(philo, "is thinking", philo->data);
}

void	*philo_thread(void *arg)
{
	t_philo *philo;
	philo = (t_philo *) arg;
	philo_init(philo);
	return (philo);
}

int	init_threads(t_data *data)
{
	int	i = data->philo_max;
	int j;
	t_philo *head = data->head;
	j = 0;
	while (j < i)
	{
		if (pthread_create(&data->head->thread, NULL, philo_thread, data->head))
		{
			printf("error thread\n");
			break ;
		}
		usleep(1 * data->philo_max);
		data->head = data->head->next;
		j++;
	}
	gettimeofday(&data->start, NULL);
	j = 0;
	while (j < i)
	{
		pthread_join(head->thread, NULL);
		head = head->next;
		j++;
	}
	return (1);
}
