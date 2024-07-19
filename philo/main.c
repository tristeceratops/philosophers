/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/19 10:32:35 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	if (ft_atoi(argv[1]) > 300)
		return (0);
	while (i <= argc)
	{
		if (argv[i] && !ft_check_str(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (0);
	}
	return (1);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].nb_meal = 0;
		data->philosophers[i].l_fork_id = i;
		data->philosophers[i].r_fork_id = (i + 1) % data->nb_philo;
		data->philosophers[i].tlm = -1;
		data->philosophers[i].data = data;
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_death = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->nb_max_eat = -1;
	if (argv[5])
		data->nb_max_eat = ft_atoi(argv[5]);
	data->dead = 0;
	data->all_ate = 0;
	data->first_time = 0;
	if (pthread_mutex_init(&data->meal_check, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_death, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_write, NULL))
		return (0);
	return (init_forks(data) && init_philo(data));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv))
	{
		printf("error args\n");
		return (1);
	}
	if (!init_data(&data, argv))
	{
		printf("error init\n");
		ft_exit(&data);
		return (1);
	}
	ft_thread(&data);
	return (0);
}
