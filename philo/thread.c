/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/15 18:10:09 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	first_fork(t_philo *philo)
{
	if (philo->l_fork_id < philo->r_fork_id)
		return (philo->l_fork_id);
	else
		return (philo->r_fork_id);
}

int	second_fork(t_philo *philo)
{
	if (philo->l_fork_id < philo->r_fork_id)
		return (philo->r_fork_id);
	else
		return (philo->l_fork_id);
}

void	philo_eat(t_philo *philo)
{
	int	f_f;
	int	s_f;

	f_f = first_fork(philo);
	s_f = second_fork(philo);
	pthread_mutex_lock(&philo->data->forks[f_f]);
	printlog(philo, philo->data, FORK, 0);
	if (philo->data->nb_philo == 1)
	{
		philo->tlm = get_current_time();
		ft_usleep(philo->data->time_death, philo->data);
		pthread_mutex_unlock(&philo->data->forks[f_f]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[s_f]);
	printlog(philo, philo->data, FORK, 0);
	pthread_mutex_lock(&philo->data->meal_check);
	printlog(philo, philo->data, EAT, 0);
	philo->tlm = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_eat, philo->data);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->data->forks[f_f]);
	pthread_mutex_unlock(&philo->data->forks[s_f]);
}

void	*routine(void *arg)
{
	t_philo		*p;
	int			d;

	p = (t_philo *)arg;
	printlog(p, p->data, THINK, 0);
	if (p->id % 2 == 0)
		ft_usleep(p->data->time_eat / 2, p->data);
	pthread_mutex_lock(&p->data->check_death);
	d = p->data->dead;
	pthread_mutex_unlock(&p->data->check_death);
	while (!d)
	{
		philo_eat(p);
		if (p->data->all_ate || d)
			break ;
		printlog(p, p->data, SLEEP, 0);
		ft_usleep(p->data->time_sleep, p->data);
		printlog(p, p->data, THINK, 0);
		pthread_mutex_lock(&p->data->check_death);
		d = p->data->dead;
		pthread_mutex_unlock(&p->data->check_death);
	}
	return (NULL);
}

void	death_checker(t_data *data, t_philo *philos, int i, long long *time)
{
	pthread_mutex_lock(&data->meal_check);
	if ((get_current_time() - philos[i].tlm) >= data->time_death)
	{
		pthread_mutex_lock(&data->check_death);
		data->dead = 1;
		pthread_mutex_unlock(&data->check_death);
		printlog(&philos[i], data, DEATH, 1);
	}
	*time = philos[i].tlm;
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
		i = 0;
		while (data->nb_max_eat != -1 && i < data->nb_philo \
			&& philos[i].nb_meal >= data->nb_max_eat)
			i++;
		if (i == data->nb_philo)
			data->all_ate = 1;
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
