/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:16:58 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/20 15:21:44 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *arg)
{
	t_data *data;
	data = (t_data *) arg;
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
		usleep(50 * data->philo_max);
		data->head = data->head->next;
		j++;
	}
	for (int j = 0; j < i; j++)
    {
        pthread_join(head->thread, NULL);
		head = head->next;
    }
	return (1);
}