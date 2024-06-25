/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:00 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/25 14:04:10 by ewoillar         ###   ########.fr       */
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

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		write(2, "Error: gettimeofday\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}