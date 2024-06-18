/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/18 15:34:58 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printlog(t_philo *philo, char *str, t_data *data)
{
	struct timeval time;
	long timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec - data->start.tv_sec) * 1000; // convert seconds to milliseconds
	timestamp += (time.tv_usec - data->start.tv_usec) / 1000; // convert microseconds to milliseconds
	printf("%-8ld %-8d %-4s\n", timestamp, philo->philo_id, str);
}

void	free_all_philo(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo;
		philo = philo->next;
		pthread_mutex_destroy(&tmp->fork_l);
		if (tmp->fork_r)
			pthread_mutex_destroy(tmp->fork_r);
		free(tmp);
	}
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i <= argc)
	{
		if (argv[i] && !ft_check_str(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

void	add_philo(t_philo **philo, int id)
{
	t_philo	*new;
	t_philo	*tmp;

	new = malloc(sizeof(t_philo));
	if (!new)
		return ;
	new->philo_id = id;
	new->isalive = 1;
	if(pthread_mutex_init(&new->fork_l, NULL) != 0)
	{
		free(new);
		return ;
	}
	new->next = NULL;
	new->prev = NULL;
	if (!*philo)
	{
		*philo = new;
		return ;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return ;
}

void	init_data(t_data *data, char **argv)
{
	data->philo_max = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->rounds = ft_atoi(argv[5]);
	else
		data->rounds = -1;
	data->is_dead = 0;
	gettimeofday(&data->start, NULL);
}

void	init_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->philo_max)
	{
		add_philo(philo, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = NULL;
	data = malloc(sizeof(t_data));
	if (!check_args(argc, argv))
	{
		ft_putstr(2, "Error: Invalid arguments\n");
		return (1);
	}
	init_data(data, argv);
	init_philo(&philo, data);
	free_all_philo(philo);
}
