/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/08 14:39:11 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_str(const char *str)
{
	if (ft_atoi(str) <= 0)
		return (0);
	while (*str)
	{
		if (!ft_isnum(*str) && *str != '+' && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	start;
	int			d;

	start = get_current_time();
	pthread_mutex_lock(&data->check_death);
	d = data->dead;
	pthread_mutex_unlock(&data->check_death);
	while (get_current_time() - start < time && !d)
		usleep(time / 10);
}

void	ft_putchar (char c, int fd)
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
        return;
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
