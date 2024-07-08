/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:01:17 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/08 15:27:35 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	if (philo->data->nb_philo == 1)
	{
		philo->time_last_meal = get_current_time();
		ft_usleep(philo->data->time_death, philo->data);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->r_fork_id]);
	printlog(philo, philo->data, FORK, 0);
	pthread_mutex_lock(&philo->data->meal_check);
	printlog(philo, philo->data, EAT, 0);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_eat, philo->data);
	philo->numb_meal++;
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork_id]);
}

void	*routine(void *arg)
{
	t_philo		*p;
	int			d;
	
	p = (t_philo *)arg;
	if (p->id % 2 == 0)
	{
		printlog(p, p->data, THINK, 0);
		ft_usleep(p->data->time_eat / 2, p->data);
	}
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

//infinite loop that constantly check if there is a dead
void	death_check(t_data *data, t_philo *philos)
{
	int	i;
	long long	time;
	
	while (!data->all_ate)
	{
		i = -1;
		pthread_mutex_lock(&data->meal_check);
		time = philos[0].time_last_meal;
		pthread_mutex_unlock(&data->meal_check);
		while (++i < data->nb_philo && !data->dead && philos[i].time_last_meal >= 0)
		{
			pthread_mutex_lock(&data->meal_check);
			if ((get_current_time() - philos[i].time_last_meal) >= data->time_death)
			{
				pthread_mutex_lock(&data->check_death);
				data->dead = 1;
				pthread_mutex_unlock(&data->check_death);
				printlog(&philos[i], data, DEATH, 1);
			}
			pthread_mutex_unlock(&data->meal_check);
			pthread_mutex_lock(&data->meal_check);
			time = philos[i].time_last_meal;
			pthread_mutex_unlock(&data->meal_check);
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->nb_max_eat != -1 && i < data->nb_philo && philos[i].numb_meal >= data->nb_max_eat)
			i++;
		if (i == data->nb_philo)
			data->all_ate = 1;
	}
}
void ft_exit(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->check_write);
}

void exit_thread(t_data *data, t_philo *philos)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	ft_exit(data);
}

int	ft_thread(t_data *data)
{
	int	i;
	t_philo	*p;
	
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