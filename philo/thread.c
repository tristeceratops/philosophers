/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:16:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/21 16:57:40 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *arg)
{
	t_data *data;
	data = (t_data *) arg;
	usleep(10 * (data->philo_max));
	printf("[%s]\n", data->time_die);
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
