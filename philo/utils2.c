/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:32:21 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/09 13:24:50 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *s, int fd)
{
	while (*s)
	{
		ft_putchar(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(long long n, int fd)
{
	char	c;

	if (n == -9223372036854775807LL - 1)
	{
		ft_putstr("−9223372036854775808", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = n + '0';
		ft_putchar(c, fd);
	}
}

void	printlog(t_philo *philo, t_data *data, char *str, int dead_call)
{
	struct timeval	t;
	long long		t_tamp;
	int				dead;

	pthread_mutex_lock(&data->check_write);
	pthread_mutex_lock(&data->check_death);
	dead = data->dead;
	pthread_mutex_unlock(&data->check_death);
	if (!dead || dead_call)
	{
		gettimeofday(&t, NULL);
		t_tamp = (t.tv_sec * 1000) + (t.tv_usec / 1000) - data->first_time;
		printf("%lld %d %s\n", t_tamp, philo->id, str);
	}
	pthread_mutex_unlock(&data->check_write);
}
