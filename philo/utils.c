/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/07/31 16:56:47 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_str(char *str)
{
	if (!isint(str))
		return (0);
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

int	ft_atoi(const char *nb)
{
	int	integer;
	int	mult;

	integer = 0;
	mult = 1;
	while (ft_isspace(*nb))
		nb++;
	if (*nb == '-' || *nb == '+')
		mult = 44 - *nb++;
	while (ft_isdigit(*nb))
		integer = (integer * 10) + (*nb++ - 48);
	return (integer * mult);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(50);
}
