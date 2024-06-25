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
	timestamp = (time.tv_sec - philo->start.tv_sec) * 1000;
	timestamp += (time.tv_usec - philo->start.tv_usec) / 1000;
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
	int	i;

	i = 0;
	while (i < data->philo_max)
	{
		data->philo[i]->philo_id = i + 1;
		data->philo[i]->data = data;
		data->philo[i]->time_die = ft_atoi(argv[2]);
		data->philo[i]->time_eat = ft_atoi(argv[3]);
		data->philo[i]->time_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data->philo[i]->rounds = ft_atoi(argv[5]);
		else
			data->philo[i]->rounds = -1;
		data->philo[i]->isalive = 1;
		data->philo[i]->forks = 0;
		data->philo[i]->start_mutext = data->start_mutext;
    	data->philo[i]->l_fork = malloc(sizeof(pthread_mutex_t));
		if (!data->philo[i]->l_fork)
		{
			printf("error alloc\n");
			return (0);
		}
		if(pthread_mutex_init(data->philo[i]->l_fork, NULL))
		{
			printf("error mutex\n");
			exit (0);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_max)
	{
		if (i + 1 < data->philo_max)
			data->philo[i]->r_fork = data->philo[i + 1]->l_fork;
		else
			data->philo[i]->r_fork = data->philo[0]->l_fork;
		i++;
	}
	return (1);
}

int	init_data(char **argv, t_data *data)
{
    int	i;

    i = 0;
    data->alive = 1;
	data->start_counter = 0;
    data->philo_max = ft_atoi(argv[1]);
    data->philo = malloc(sizeof(t_philo *) * data->philo_max);
    if (data->philo == NULL) 
	{
        printf("error malloc\n");
        return (0);
    }
    while (i < data->philo_max) 
	{
        data->philo[i] = malloc(sizeof(t_philo));
        if (data->philo[i] == NULL) {
            printf("error malloc\n");
            return (0);
        }
        i++;
    }
    if(pthread_mutex_init(&data->start_mutext, NULL)) {
        printf("error mutex\n");
        return (0);
    }
    return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error: Malloc\n");
		return (1);
	}
	printf("init data\n");
	init_data(argv, data);
	printf("init philo\n");
	init_philo(argv, data);
	printf("init thread\n");
	init_threads(data);
}
