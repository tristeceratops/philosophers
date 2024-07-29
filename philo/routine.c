/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:40:45 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/29 10:33:59 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_last(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	if (philo->data->nb_philo == 1)
		return (is_solo(philo));
	pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	printlog(philo, philo->data, EAT, 0);
	pthread_mutex_lock(&philo->data->meal_check);
	philo->tlm = get_current_time();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
}

void	*routine_last(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&p->data->check_death);
		if (p->data->dead || p->data->all_ate)
		{
			pthread_mutex_unlock(&p->data->check_death);
			break ;
		}
		pthread_mutex_unlock(&p->data->check_death);
		philo_eat_last(p);
		sleepy(p);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	if (philo->data->nb_philo == 1)
		return (is_solo(philo));
	usleep(100);
	pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	printlog(philo, philo->data, EAT, 0);
	pthread_mutex_lock(&philo->data->meal_check);
	philo->tlm = get_current_time();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
	{
		printlog(p, p->data, THINK, 0);
		ft_usleep(p->data->time_eat / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&p->data->check_death);
		if (p->data->dead || p->data->all_ate)
		{
			pthread_mutex_unlock(&p->data->check_death);
			break ;
		}
		pthread_mutex_unlock(&p->data->check_death);
		philo_eat(p);
		sleepy(p);
	}
	return (NULL);
}
