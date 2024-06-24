/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewoillar <ewoillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:44:48 by ewoillar          #+#    #+#             */
/*   Updated: 2024/06/24 13:40:50 by ewoillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printlog(t_philo *philo, char *str, t_data *data)
{
	struct timeval time;
	long timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec - philo->start.tv_sec) * 1000;
	timestamp += (time.tv_usec - philo->start.tv_usec) / 1000;
	printf("%-6ld %-6d %-4s\n", timestamp, philo->philo_id, str);
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
int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
	{
		ft_putstr(2, "Error: Invalid arguments\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr(2, "Error: Malloc\n");
		return (1);
	}
	data->philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_data(data, argv);
	init_threads(data);
	free_all(data);
}
