/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/30 13:55:53 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_checker(t_data *data, t_philo *philos, int i, long long *time)
{
	long long	current_time;
	long long	tlm;

	pthread_mutex_lock(&data->meal_check);
	current_time = get_current_time();
	tlm = philos[i].tlm;
	pthread_mutex_unlock(&data->meal_check);
	if ((current_time - tlm) >= data->time_death)
	{
		pthread_mutex_lock(&data->check_death);
		data->dead = 1;
		pthread_mutex_unlock(&data->check_death);
		printlog(&philos[i], data, DEATH, 1);
	}
	pthread_mutex_lock(&data->meal_check);
	*time = philos[i + 1].tlm;
	pthread_mutex_unlock(&data->meal_check);
}

void	death_check(t_data *data, t_philo *philos)
{
	int			i;
	long long	time;

	while (1)
	{
		i = -1;
		pthread_mutex_lock(&data->meal_check);
		time = philos[0].tlm;
		pthread_mutex_unlock(&data->meal_check);
		while (++i < data->nb_philo && !data->dead && philos[i].tlm >= 0)
			death_checker(data, philos, i, &time);
		if (data->dead)
			break ;
		all_ate(data, philos);
		if (data->all_ate)
			break ;
		usleep(50);
	}
}

int	ft_thread(t_data *data)
{
	int			i;
	t_philo		*p;

	i = 0;
	p = data->philosophers;
	data->start_time = get_current_time();
	while (i < data->nb_philo)
	{
		if (is_parent(data))
		{
			printf("fork at %d\n", i + 1);
			data->philo_pid[i++] = fork();
		}
	}
	if (!is_parent)
	{
		printf("ici on fait la routine là, hop hop hop yes life\n");
		//routine
	}
	waiting_all(data);
	ft_exit(data);
	return (0);
}
