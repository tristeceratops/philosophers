/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:01:10 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/30 15:20:28 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*wait_routine(void *p)
{
	t_philo	*philo;
	t_data	*data;
	int		status;

	philo = (t_philo *)p;
	data = philo->data;
	waitpid(data->philo_pid[philo->id - 1], &status, 0);
	if (status == 1)
	{
		pthread_mutex_lock(&data->check_death);
		data->dead = 1;
		pthread_mutex_unlock(&data->check_death);
	}
	return (NULL);
}

int	waiting_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		//check error creation
		pthread_create(&data->check_threads[i], NULL, wait_routine, &(data->philosophers[i++]));
	}
	i = 0;
	while (i < data->nb_philo)
		pthread_detach(&data->check_threads[i++]);	
}