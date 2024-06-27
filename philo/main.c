/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/25 14:01:51 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printlog(t_philo *philo, char *str)
{
	struct timeval	time;
	long			timestamp;

	gettimeofday(&time, NULL);
	printf("%ld %d %s\n", timestamp, philo->philo_id, str);
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

int	init_philo(char **argv, t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_max)
	{
		data->philo[i]->philo_id = i + 1;
		data->philo[i]->isalive = 1;
		data->philo[i]->time_start = 0;
		data->philo[i]->time_last_meal = 0;
		data->philo[i]->data = data;
		if (pthread_mutex_init(&data->philo[i]->l_fork, NULL))
			return (1);
		if (i == data->philo_max - 1)
			data->philo[i]->r_fork = &data->philo[0]->l_fork;
		else
			data->philo[i]->r_fork = &data->philo[i + 1]->l_fork;
		i++;
	}
	return (0);
}

int	init_data(char **argv, t_data *data)
{
	data->philo_max = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->rounds = ft_atoi(argv[5]);
	else
		data->rounds = -1;
	data->alive = 1;
	if (pthread_mutex_init(&data->start_mutext, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat_mutext, NULL))
		return (1);
	if (pthread_mutex_init(&data->finish_mutext, NULL))
		return (1);
    return (0);
}

int	init(t_thread *t, const char **argv)
{
	int	i;

	i = 0;
	i += init_data(argv, t->data);
	i += init_philo(argv, t->data);
	return (i);
}

void	ft_exit(t_thread *t)
{
	int	i;

	i = 0;
	while (i < t->data->philo_max)
	{
		pthread_mutex_destroy(&t->data->philo[i]->l_fork);
		i++;
	}
	pthread_mutex_destroy(&t->data->start_mutext);
	pthread_mutex_destroy(&t->data->eat_mutext);
	pthread_mutex_destroy(&t->data->finish_mutext);
	free(t->data->philo);
	free(t->data);
}

int	main(int argc, char **argv)
{
	t_thread t;

	if (!check_args(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	t.data = malloc(sizeof(t_data));
	t.philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!t.data && !t.philo)
	{
		printf("Error: Malloc\n");
		return (1);
	}
	if (init(&t, argv) && !thread(&t))
	{
		ft_exit(&t);
		return (1);
	}
}
