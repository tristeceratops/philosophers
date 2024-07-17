/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/17 18:04:25 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	if (philo->data->nb_philo == 1)
	{
		is_solo(philo);
		return ;
	}
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
	else
		pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	pthread_mutex_lock(&philo->data->meal_check);
	printlog(philo, philo->data, EAT, 0);
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
	int			d;
	int			all_ate;

	p = (t_philo *)arg;
	printlog(p, p->data, THINK, 0);
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_eat / 2);
	pthread_mutex_lock(&p->data->check_death);
	d = p->data->dead;
	all_ate = p->data->all_ate;
	pthread_mutex_unlock(&p->data->check_death);
	while (!d)
	{
		philo_eat(p);
		if (all_ate || d)
			break ;
		sleepy(p);
		pthread_mutex_lock(&p->data->check_death);
		d = p->data->dead;
		all_ate = p->data->all_ate;
		pthread_mutex_unlock(&p->data->check_death);
	}
	return (NULL);
}

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
	
	while (!data->all_ate)
	{
		i = -1;
		pthread_mutex_lock(&data->meal_check);
		time = philos[0].tlm;
		pthread_mutex_unlock(&data->meal_check);
		while (++i < data->nb_philo && !data->dead && philos[i].tlm >= 0)
		{
			death_checker(data, philos, i, &time);
		}
		if (data->dead)
			break ;
		all_ate(data, philos);
		usleep(80);
	}
}

int	ft_thread(t_data *data)
{
	int			i;
	t_philo		*p;

	i = 0;
	p = data->philosophers;
	data->first_time = get_current_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&(p[i].thread), NULL, routine, &(p[i])))
			return (1);
		i++;
	}
	death_check(data, data->philosophers);
	exit_thread(data, p);
	return (0);
}
