/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/20 14:50:45 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printlog(t_philo *philo, char *str, t_data *data)
{
	struct timeval time;
	long timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec - data->start.tv_sec) * 1000;
	timestamp += (time.tv_usec - data->start.tv_usec) / 1000;
	printf("%-8ld %-8d %-4s\n", timestamp, philo->philo_id, str);
}

void	free_all_philo(t_data *data, t_philo *philo)
{
	t_philo	*tmp;

	while (philo->philo_id < data->philo_max)
	{
		tmp = philo;
		philo = philo->next;
		pthread_mutex_destroy(tmp->l_fork);
		if (tmp->r_fork)
			pthread_mutex_destroy(tmp->r_fork);
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
void	philo_rfork(t_philo *philo)
{
	while (philo->r_fork == NULL)
	{
		philo->r_fork = philo->next->l_fork;
		philo = philo->next;
	}
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
	new->l_fork = malloc(sizeof(pthread_mutex_t));
	new->r_fork = NULL;
	if(pthread_mutex_init(new->l_fork, NULL) != 0)
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
void connect_first_and_last(t_philo **philo) {
	
	t_philo *first;
	t_philo *last;
	
	if (*philo == NULL)
		return ;
	first = *philo;
	last = *philo;
	while (last->next != NULL)
		last = last->next;
	if (first != last)
	{
		first->prev = last;
		last->next = first;
	}
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
	connect_first_and_last(philo);
	philo_rfork(*philo);
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
	data->head = philo;
	init_threads(data, philo);
	free_all_philo(data, philo);
}
