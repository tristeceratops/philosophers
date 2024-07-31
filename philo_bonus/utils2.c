/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:32:21 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/31 14:55:29 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleepy(t_philo *philo)
{
	printlog(philo, philo->data, SLEEP, 0);
	ft_usleep(philo->data->time_sleep);
	printlog(philo, philo->data, THINK, 0);
}

// void	is_solo(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->meal_check);
// 	philo->tlm = get_current_time();
// 	pthread_mutex_unlock(&philo->data->meal_check);
// 	ft_usleep(philo->data->time_death);
// 	pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
// }

void	all_ate(t_data *data, t_philo *philos)
{
	int		nb_meal;
	int		i;

	i = 0;
	pthread_mutex_lock(&data->meal_check);
	nb_meal = philos[i].nb_meal;
	pthread_mutex_unlock(&data->meal_check);
	while (data->nb_max_eat != -1 && i < data->nb_philo \
			&& nb_meal >= data->nb_max_eat)
	{
		i++;
		pthread_mutex_lock(&data->meal_check);
		nb_meal = philos[i].nb_meal;
		pthread_mutex_unlock(&data->meal_check);
	}
	pthread_mutex_lock(&data->check_death);
	if (i == data->nb_philo)
		data->all_ate = 1;
	pthread_mutex_unlock(&data->check_death);
}

void	printlog(t_philo *philo, t_data *data, char *str, int dead_call)
{
	struct timeval	t;
	long long		t_tamp;
	int				dead;
	int				all_ate;

	pthread_mutex_lock(&data->check_write);
	pthread_mutex_lock(&data->check_death);
	dead = data->dead;
	all_ate = data->all_ate;
	pthread_mutex_unlock(&data->check_death);
	if ((!dead && !all_ate) || dead_call)
	{
		gettimeofday(&t, NULL);
		t_tamp = (t.tv_sec * 1000) + (t.tv_usec / 1000) - data->start_time;
		printf("%lld %d %s\n", t_tamp, philo->id, str);
	}
	pthread_mutex_unlock(&data->check_write);
}

int		is_parent(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo_pid[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	isint(char *n)
{
	int		nbr;
	long	nbr2;
	int		i;
	int		j;

	i = 0;
	while (n[i] == '+' || n[i] == '-')
		i++;
	j = i;
	while (ft_isdigit(n[j]))
		j++;
	if (j != ft_strlen(n) || i == j)
		return (0);
	nbr = ft_atoi(n);
	nbr2 = ft_atol(n);
	n += i;
	if (nbr == nbr2)
	{
		if (nbr >= 0 && ft_strlen(n) == ft_intlen(nbr))
			return (1);
		if (nbr < 0 && ft_strlen(n) + 1 == ft_intlen(nbr))
			return (1);
	}
	return (0);
}
