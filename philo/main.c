/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/08 16:44:53 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printlog(t_philo *philo, t_data *data, char *str, int dead_call)
{
	struct timeval	time;
	long long		timestamp;
	int				dead;
	
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&data->check_write);
	pthread_mutex_lock(&data->check_death);
	dead = data->dead;
	pthread_mutex_unlock(&data->check_death);
	if (!dead || dead_call)
	{
		timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000) - data->first_time;
		// ft_putnbr_fd(timestamp, 1);
		// ft_putstr(" ", 1);
		// ft_putnbr_fd((long long)philo->id, 1);
		// ft_putstr(" ", 1);
		// ft_putstr(str, 1);
		// ft_putstr("\n", 1);
		printf("%lld %d %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(&data->check_write);
}

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
		data->philosophers[i].numb_meal = 0;
		data->philosophers[i].l_fork_id = i;
		data->philosophers[i].r_fork_id = (i + 1) % data->nb_philo;
		data->philosophers[i].time_last_meal = -1;
		data->philosophers[i].data = data;
		data->philosophers[i].forks = 0;
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
		ft_putstr("error args\n", 2);
		ft_exit(&data);
		return (1);
	}
	if (!init_data(&data, argv))
	{
		ft_putstr("error init\n", 2);
		ft_exit(&data);
		return (1);
	}
	ft_thread(&data);
	return (0);	
}
