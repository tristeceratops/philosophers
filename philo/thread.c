/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:16:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/21 14:07:23 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_meal(t_data *data)
{
	if (data->head->philo_id % 2 == 1)
	{
		pthread_mutex_lock(data->head->l_fork);
		forking(data, data->head);
		pthread_mutex_lock(data->head->r_fork);
		forking(data, data->head);
	}
	else
	{
		thinking(data, data->head);
	}
}

void	*philo_thread(void *arg)
{
	t_data *data;
	data = (t_data *) arg;
	gettimeofday(&data->start, NULL);
	init_meal(data);
	usleep(10 * (data->philo_max));
	meal(data, data->head);
	pthread_exit(0);
}

int	init_threads(t_data *data, t_philo *philo)
{
	int	i = data->philo_max;
	int j;
	t_philo *head = philo;
	j = 0;
	while (j < i)
	{
		if (pthread_create(&philo->thread, NULL, philo_thread, data))
		{
			printf("error thread\n");
			break ;
		}
		usleep(10 * (data->philo_max));
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
